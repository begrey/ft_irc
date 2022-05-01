/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:20 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/13 23:24:01 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETCORE_HPP
#define NETCORE_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <poll.h>
#include <fcntl.h>
#include <string.h>

#include "../ServDataStruct.hpp"
#include "../Utils/LogTool.hpp"
#include "../Utils/CommQueue.hpp"
#include "../Utils/KeyInputTool.hpp"
#include "../Utils/ErrorHandling.hpp"
#include "../Utils/libft/libft.h"
#include "../IRCCore/IRCCore.hpp"

#define BUFFER_SIZE 100
#define LISTEN_QUEUE_SIZE 5
#define LISTEN_IDX 0

class NetCore
{
/* Functions */
public:
    NetCore(LogTool* logCore);
    ~NetCore();

    bool InitializeNetCore(ServerExecuteSpecification* executeSpecification);
    void RunNetLoop(IRCCore* ircCore, CommQueue* inputQueue, CommQueue* outputQueue);
    void DestroyNetCore();

    int GetMaxFdSize() const;

public:
    static std::string ConvFdToIP(int sockfd);

/* Variables */
private:
    pollfd *pollFdPool;
    int maxFdSize;
    int searchFdScope;
    
    LogTool* logCore;
};

#endif