/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:17 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:50:55 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCORE_HPP
#define IRCCORE_HPP

#include <map>
#include "../Utils/ft_containers/map/map.hpp"
#include "../Utils/ft_containers/vector/vector.hpp"
#include "../Utils/CommQueue.hpp"
#include "../Utils/LogTool.hpp"
#include "../Utils/NetSupportUtil.hpp"
#include "IRCDataStruct.hpp"

class IRCCore;

struct CommandProcessCell
{
    std::string keyCommand;
    void(IRCCore::*processFunction)(int pollidx, std::string msg, CommQueue* outputQueue);
};

class IRCCore
{
/* Functions */
public:
    IRCCore();
    ~IRCCore();

    std::string getPassword();
    CommandProcessCell MakeCommandCell(std::string key, void(IRCCore::*processFunction)(int pollidx, std::string msg, CommQueue* outputQueue));
    bool InitializeIRCCore(int maxUserNum, std::string serverPassword, LogTool* logCore);
    void ProcessIRC(CommQueue* inputQueue, CommQueue* outputQueue);

private:
    void clearUserCell(int idx);

public:
    void PF_IRCCORE(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_CONNECT(int pollidx);
    void PF_PASS(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_NICK(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_USER(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_JOIN(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_QUIT(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_PART(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_TOPIC(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_KICK(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_PRIVMSG(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_NOTICE(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_WHO(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_NAME(int pollidx, std::string msg, CommQueue* outputQueue);
    void PF_END(int pollidx, std::string msg, CommQueue* outputQueue);
    bool PF_PNU(int pollidx, std::string keyCommand, CommQueue* outputQueue);

/* Variables */
private:
    int userNumber;
    int userMaxNumber;
    
    User_t* userList;
    
    std::map<std::string, Channel_t> channelPool;

    std::vector<CommandProcessCell> commandPool;

    std::string serverPassword;

    LogTool* logCore;
};

#endif