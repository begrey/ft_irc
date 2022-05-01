/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:20 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:55:46 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetCore.hpp"

NetCore::NetCore(LogTool* logCore)
{
    this->logCore = logCore;
    this->searchFdScope = 10;
    this->maxFdSize = 256;
    this->pollFdPool = new pollfd[maxFdSize];
    if (pollFdPool == NULL)
    {
        logCore->FatalError("Error: Allocation fail on pollFdPool.");
    }
}
NetCore::~NetCore()
{
    if (pollFdPool != NULL)
    {
        delete[] pollFdPool;
    }
}

bool NetCore::InitializeNetCore(ServerExecuteSpecification* executeSpecification)
{
    logCore->WriteLog("NetCore initializeing...");

    int listenFd;
    sockaddr_in listenSocket;

    listenFd = ErrorHandle(-1, socket(PF_INET, SOCK_STREAM, 0), 
                    "NetCore Initialize Error: listenFd socket() fail.", logCore);

    memset(&listenSocket, 0, sizeof(listenSocket));

    listenSocket.sin_family = AF_INET;
    listenSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    listenSocket.sin_port = htons(executeSpecification->port);

    ErrorHandle(-1, bind(listenFd, (sockaddr*)&listenSocket, sizeof(listenSocket)),
                "NetCore Initialize Error: Can not bind.", logCore);

    ErrorHandle(-1, listen(listenFd, LISTEN_QUEUE_SIZE),
                "NetCore Initialize Error: Listen fail.", logCore);

    fcntl(listenFd, F_SETFL, O_NONBLOCK);

    pollFdPool[LISTEN_IDX].fd = listenFd;
    pollFdPool[LISTEN_IDX].events = POLLIN;
    pollFdPool[LISTEN_IDX].revents = 0;

    for (int i = 1; i < maxFdSize; i++)
    {
        pollFdPool[i].fd = -1;
    }

    init_keyboard();

    logCore->WriteLog("NetCore initialize succeed.");
    return true;
}

void NetCore::RunNetLoop(IRCCore* ircCore, CommQueue* inputQueue, CommQueue* outputQueue)
{
    bool bRun = true;

    int connectFd;
    sockaddr_in connectSocket;
    socklen_t addrSize;
    char buf[BUFFER_SIZE];
    int len = 0;

    logCore->WriteLog("NetCore running...");

    while (bRun)
    {
        if (linux_kbhit() == 1)
        {
            char keyInput = linux_getch();
            switch (keyInput)
            {
            case 'q':
                logCore->WriteLog("Server close...");
                bRun = false;
                break;
            default:
                break;
            }
        }
        if (!bRun)
        {
            break;
        }

        int result = poll(pollFdPool, maxFdSize, 10000);

        /* New connection */
        if (result > 0)
        {
            if (pollFdPool[LISTEN_IDX].revents == POLLIN)
            {
                // New connection requested.
                connectFd = accept(pollFdPool[LISTEN_IDX].fd, (sockaddr*)&connectSocket, &addrSize);

                if (connectFd != -1)
                {
                    std::string logStr = "New connection to " + ConvFdToIP(connectFd) + ".";
                    logCore->WriteLog(logStr);

                    fcntl(connectFd, F_SETFL, O_NONBLOCK);

                    for (int i = 1; i < maxFdSize; i++)
                    {
                        if (pollFdPool[i].fd == -1)
                        {
                            pollFdPool[i].fd = connectFd;
                            pollFdPool[i].events = POLLIN;
                            pollFdPool[i].revents = 0;

                            if (i + 1 > searchFdScope)
                            {
                                searchFdScope = i + 1;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    logCore->WriteLog("Error: Accept fail.");
                }
            }

            /* Receive */
            for (int i = 1; i < searchFdScope; i++)
            {
                switch (pollFdPool[i].revents)
                {
                    case 0:
                        break;
                    case POLLIN:
                    {
                        len = read(pollFdPool[i].fd, buf, BUFFER_SIZE);
                        if (len == 0)
                        {
                            logCore->WriteLog("Warnning: Adnormal connection detective. Disconnect.");
                            close(pollFdPool[i].fd);
                            pollFdPool[i].fd = -1;
                            if (i + 1 == searchFdScope)
                            {
                                int newScope = i;
                                for (; newScope >= 10; newScope--)
                                {
                                    if (pollFdPool[newScope].fd != -1)
                                    {
                                        searchFdScope = newScope + 1;
                                        break;
                                    }
                                }
                                if (newScope == 10)
                                {
                                    searchFdScope = 10;
                                }
                            }
                            continue;
                        }
                        buf[len - 1] = '\0';
                        std::string logStr = "Data received from " + ConvFdToIP(pollFdPool[i].fd) + ". " + std::string(buf);
                        logCore->WriteLog(logStr);
                        fflush(stdout);
                        // Push input to queue.
                        ft::vector<std::string> line = Utils::split(std::string(buf), '\n');
                        for (int j = 0; j < line.size(); j++)
                        {
                            inputQueue->push(i, line.at(j));
                        }
                        break;
                    }
                    default:
                        close(pollFdPool[i].fd);
                        pollFdPool[i].fd = -1;
                        pollFdPool[i].revents = 0;
                        if (i + 1 == searchFdScope)
                        {
                            int newScope = i;
                            for (; newScope >= 10; newScope--)
                            {
                                if (pollFdPool[newScope].fd != -1)
                                {
                                    searchFdScope = newScope + 1;
                                    break;
                                }
                            }
                            if (newScope == 10)
                            {
                                searchFdScope = 10;
                            }
                        }
                        break;
                }
            }
            /* IRCCore precess */
            ircCore->ProcessIRC(inputQueue, outputQueue);

            /* Send and connection process */
            if (outputQueue->size() > 0)
            {
                while (outputQueue->size() != 0)
                {
                    QueueCell outputCell = outputQueue->front();
                    if (pollFdPool[outputCell.pollIdx].fd != -1)
                    {
                        std::cout << outputCell.buffer << std::endl;
                        //outputCell.buffer += "\n";
                        write(pollFdPool[outputCell.pollIdx].fd, outputCell.buffer.c_str(), outputCell.buffer.length());
                    }
                    else
                    {
                        inputQueue->push(outputCell.pollIdx, "IRCCORE GHOSTDTECT");
                    }
                    outputQueue->pop();
                }
            }
        }
    }
}

void NetCore::DestroyNetCore()
{
    for (int i = 0; i < searchFdScope; i++)
    {
        if (pollFdPool[i].fd != -1)
        {
            close(pollFdPool[i].fd);
            pollFdPool[i].fd = -1;
            pollFdPool[i].revents = 0;
        }
    }

    close_keyboard();
}

int NetCore::GetMaxFdSize() const { return maxFdSize; }

std::string NetCore::ConvFdToIP(int sockfd)
{
    sockaddr_in addr;
    int len = sizeof(addr);

    getpeername(sockfd, (sockaddr*)&addr, (socklen_t*)&len);
    return std::string(inet_ntoa(addr.sin_addr));
}