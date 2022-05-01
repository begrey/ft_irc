/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:08:47 by kwonjimin         #+#    #+#             */
/*   Updated: 2022/01/14 11:05:00 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"
IRCCore::IRCCore()
{
    userList = NULL;
}
IRCCore::~IRCCore()
{
    if (userList != NULL) { 
        delete[] userList; 
    }
}
std::string IRCCore::getPassword()
{
    return this->serverPassword;
}
CommandProcessCell IRCCore::MakeCommandCell(std::string key, void(IRCCore::*processFunction)(int pollidx, std::string msg, CommQueue* outputQueue))
{
    CommandProcessCell temp;
    temp.keyCommand = key;
    temp.processFunction = processFunction;
    return temp;
}

bool IRCCore::InitializeIRCCore(int maxUserNum, std::string serverPassword, LogTool* logCore)
{
    this->userNumber = 0;
    this->userMaxNumber = maxUserNum - 1;
    if (userMaxNumber <= 0) { return false; }
    userList = new User_t[userMaxNumber];
    if (userList == NULL) { return false; }
    for (int i = 0; i < userMaxNumber; i++)
    {
        clearUserCell(i);
    }
    this->serverPassword = serverPassword;
    this->logCore = logCore;

    // commandPool initialize.
    commandPool.push_back(MakeCommandCell("IRCCORE", &IRCCore::PF_IRCCORE));
    commandPool.push_back(MakeCommandCell("PASS", &IRCCore::PF_PASS));
    commandPool.push_back(MakeCommandCell("NICK", &IRCCore::PF_NICK));
    commandPool.push_back(MakeCommandCell("USER", &IRCCore::PF_USER));
    commandPool.push_back(MakeCommandCell("JOIN", &IRCCore::PF_JOIN));
    commandPool.push_back(MakeCommandCell("TOPIC", &IRCCore::PF_TOPIC));
    commandPool.push_back(MakeCommandCell("QUIT", &IRCCore::PF_QUIT));
    commandPool.push_back(MakeCommandCell("PART", &IRCCore::PF_PART));
    commandPool.push_back(MakeCommandCell("PRIVMSG", &IRCCore::PF_PRIVMSG));
    commandPool.push_back(MakeCommandCell("NOTICE", &IRCCore::PF_NOTICE));
    commandPool.push_back(MakeCommandCell("WHO", &IRCCore::PF_WHO));
    commandPool.push_back(MakeCommandCell("KICK", &IRCCore::PF_KICK));
    commandPool.push_back(MakeCommandCell("NAME", &IRCCore::PF_NAME));
    commandPool.push_back(MakeCommandCell("END", &IRCCore::PF_END));
    
    return true;
}

#include <stack>

void IRCCore::ProcessIRC(CommQueue* inputQueue, CommQueue* outputQueue)
{
    std::stack<std::string> line;
    ft::vector<QueueCell>::iterator iter;
    while (inputQueue->size() != 0)
    {
        QueueCell inputCell = inputQueue->front();
        inputQueue->pop();

        std::string keyCommand;
        char* tempStr = (char*)inputCell.buffer.c_str();
        int curs = 0;
        for (curs = 0; curs < inputCell.buffer.length(); curs++)
        {
            if (tempStr[curs] == ' ')
                break;
            if (tempStr[curs + 1] == '\0')
            {
                curs += 1;
                break;
            }
        }
        tempStr[curs] = '\0';
        keyCommand = std::string(tempStr);
        for (int i = 0; i < keyCommand.length(); i++)
            keyCommand[i] = toupper(keyCommand[i]);
        tempStr[curs] = '_';

        for (int i = 0; i < commandPool.size(); i++)
        {
            if (commandPool[i].keyCommand == keyCommand)
            {
                std::string msg;
                if (tempStr[curs + 1] != '\0')
                {
                    msg = inputCell.buffer.substr(keyCommand.length() + 1);
                    if (msg[msg.length() - 1] == '\r')
                    {
                        msg = msg.substr(0, msg.length() - 1);
                    }
                }
                else
                {
                    msg = "";
                }
                if (!IRCCore::PF_PNU(inputCell.pollIdx, commandPool[i].keyCommand, outputQueue))
                {
                    break;
                }
                void (IRCCore::*processFunction)(int pollidx, std::string msg, CommQueue* outputQueue);
                processFunction = commandPool[i].processFunction;
                (this->*processFunction)(inputCell.pollIdx , msg, outputQueue);
                break;
            }
        }
    }
}

void IRCCore::clearUserCell(int idx)
{
    userList[idx].bFill = false;
    userList[idx].bAuth = false;
    userList[idx].bUser = false;
    userList[idx].bNick = false;
    userList[idx].fdPoolIdx = -1;
    userList[idx].nick = "";
    userList[idx].user = "";
    userList[idx].hostname = "";
    userList[idx].joinChannelKeyPool.clear();
}