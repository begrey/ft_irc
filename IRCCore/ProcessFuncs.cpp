/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessFuncs.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:17 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 11:30:28 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"
#include "../Utils/IRCSupportUtil.hpp"
#include "../Define.hpp"

void IRCCore::PF_END(int pollidx, std::string msg, CommQueue* outputQueue)
{
    std::cout << "서버 강제종료 합니다. (우리만의 비~밀 ^_<)" << std::endl;
    exit(0);
}

void IRCCore::PF_IRCCORE(int pollidx, std::string msg, CommQueue* outputQueue)
{
    if (msg == "GHOSTDTECT")
    {
        for (int i = 0; i < userMaxNumber; i++)
        {
            if (userList[i].bFill)
            {
                if (userList[i].fdPoolIdx == pollidx)
                {
                    userNumber--;
                    clearUserCell(i);
                    break;
                }
            }
        }
    }
}

void IRCCore::PF_CONNECT(int pollidx)
{
    userNumber++;
    for (int i = 0; i < userMaxNumber; i++)
    {
        if (!userList[i].bFill)
        {
            userList[i].bFill = true;
            userList[i].bAuth = true;
            userList[i].fdPoolIdx = pollidx;
            break;
        }
    }
}

void IRCCore::PF_PASS(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (idx == -1 && msg == getPassword())
    {
        PF_CONNECT(pollidx);
        return;
    }
    if (msg.length() == 0)
    {
        if (idx == -1)
        {
            outputQueue->push(pollidx, ErrorMsg(ERR_NEEDMOREPARAMS, ":Not enough parameters:("));
            return ;
        }
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters:("));
        return;
    }
    else if (msg == getPassword())
    {
        if (userList[idx].bAuth == true)
        {
            outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_ALREADYREGISTERED, ":You may not reregister:("));
            return;
        }
    }
    else
    {
        if (idx == -1)
        { 
            outputQueue->push(pollidx, ErrorMsg(ERR_NOSUCHPASS, ":Invalid Password"));
            return ;
        }
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOSUCHPASS, ":Invalid Password"));
    }
}

void IRCCore::PF_NICK(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (msg.length() == 0)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NONICKNAMEGIVEN, ":No nickname given"));
        return;
    }
    else if (msg.length() > 9)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NICKTOOLONG, ":The NICK cannot exceed 9 characters."));
        return;
    }
    else
    {
        if (!CheckNickname(msg))
        {
            outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_ERRONEUSNICKNAME, ":Erroneus nickname"));
            return;
        }
        for (int i = 0; i < userNumber; i++)
        {
            if (msg == userList[i].nick)
            {
                outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NICKNAMEINUSE, ":Nickname is already in use:("));
                return;  
            }
        }
        if (userList[idx].bUser == false)
        {
            userList[idx].nick = msg;
            userList[idx].bNick = true;
            outputQueue->push(pollidx, CommandMsg(userList[idx], msg, "", "NICK"));
            return;
        }
    }

    std::string msgToNick = CommandMsg(userList[idx], msg, "", "NICK");
    userList[idx].nick = msg;
    for (int i = 0; i < userNumber; i++)
    {
        outputQueue->push(userList[i].fdPoolIdx, msgToNick);
    }
}

void IRCCore::PF_USER(int pollidx, std::string msg, CommQueue* outputQueue)
{
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (msg.length() == 0 || arguments.size() != 4)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters"));
        return;
    }
    if (userList[idx].bUser == true)
    {
        std::string welcome = ReplyMsg(userList[idx], RPL_WELCOME, ":Welcome to the ft_irc Server!", "");
        outputQueue->push(pollidx, welcome);
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_ALREADYREGISTERED, ":You may not reregister"));
        return;
    }
    userList[idx].user = arguments.at(0);
    userList[idx].hostname = arguments.at(0);
    userList[idx].bUser = true;
    std::string welcome = ReplyMsg(userList[idx], RPL_WELCOME, ":Welcome to the ft_irc Server!", "");
    outputQueue->push(pollidx, welcome);
}

void IRCCore::PF_JOIN(int pollidx, std::string msg, CommQueue* outputQueue)
{
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (arguments.size() < 1)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters"));
        return;
    }
    std::string channel = arguments.at(0);
    if ( userList[idx].joinChannelKeyPool.size() > 9)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_TOOMANYCHANNELS, ":You have joined too many channels"));
        return;
    }
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(channel);
    if (CheckChannelName(channel) == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_CHANPREFIX, channel + " :Cannot join channel: Channel name must start with a hash mark (#)"));
        return;
    }
    else if (channelIter == channelPool.end())
    {
        channelPool.insert(std::pair<std::string, Channel_t>(channel, InitChannel()));
        channelPool[channel].memberIdxPool.push_back(userList[idx].fdPoolIdx);
        userList[idx].joinChannelKeyPool.insert(std::pair<std::string, bool>(channel, true));
    }
    else 
    {
        channelPool[channel].memberIdxPool.push_back(userList[idx].fdPoolIdx);
        userList[idx].joinChannelKeyPool.insert(std::pair<std::string, bool>(channel, false));
    }
    std::string msgToJoin = CommandMsg(userList[idx], "", channel, "JOIN");
    MessageToChannel(channelPool, channel, outputQueue, msgToJoin);
    PF_TOPIC(pollidx, channel, outputQueue);
    
}

void IRCCore::PF_TOPIC(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    if (arguments.size() != 1 && arguments.size() != 2)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters"));
        return;
    }
    std::string channelName = arguments.at(0);
    std::string topic = "";
    if (arguments.size() == 2)
        topic = arguments.at(1);
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(channelName);
    if (channelIter == channelPool.end())
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOSUCHCHANNEL, ":No such channel"));
        return;  
    }
    if (FindUserInChannel(channelName, userList[idx]) == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOTONCHANNEL, ":You're not on that channel", channelName));
        return;
    }
    if (arguments.size() == 2)
    {
        if (userList[idx].joinChannelKeyPool[channelName] == false)
        {
            outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_CHANOPRIVSNEEDED, ":You're not channel operator", channelName));
            return;
        }
        else
        {
            (*channelIter).second.topic = topic;
            MessageToChannel(channelPool, channelName, outputQueue, CommandMsg(userList[idx], topic, channelName, "TOPIC"));
        }
    }
    else
    {
        if ((*channelIter).second.topic == "")
        {
            outputQueue->push(pollidx, ReplyMsg(userList[idx], "331", "No topic is set", channelName));
        }
        else
        {
            outputQueue->push(pollidx, ReplyMsg(userList[idx], "332", (*channelIter).second.topic, channelName));
        }
    }
}
void IRCCore::PF_QUIT(int pollidx, std::string msg, CommQueue* outputQueue){
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    std::string message;
    if (arguments.at(0) == "")
        message = userList[idx].nick + " is Gone.";
    else 
        message = arguments.at(0);
    std::map<std::string, bool>::iterator iter;
    iter = userList[idx].joinChannelKeyPool.begin();
    size_t channelNum = userList[idx].joinChannelKeyPool.size();
    std::string* channelName = new std::string[channelNum];
    for (int i = 0; iter != userList[idx].joinChannelKeyPool.end(); iter++)
    {
        channelName[i] = (*iter).first;
        i++;
    }
    for (size_t i = 0; i < channelNum; i++)
    {
        PF_PART(pollidx, channelName[i], outputQueue);
    }
    delete [] channelName;
    outputQueue->push(pollidx, CommandMsg(userList[idx], message, "", "QUIT"));
    clearUserCell(FindUserById(pollidx, userMaxNumber, userList));
    std::cout << "서버 퇴장합니다~\n";
}

void IRCCore::PF_PART(int pollidx, std::string msg, CommQueue* outputQueue){
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    ft::vector<std::string> arguments = Utils::split(msg, ' ');

    if (arguments.size() < 1)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters"));
        return;
    }
    std::string channel = arguments.at(0);
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(channel);
    if (channelIter == channelPool.end())
    {
        outputQueue->push(pollidx,  ErrorMsg(userList[idx], ERR_NOSUCHCHANNEL, channel + ":No such channel"));
        return;  
    }
    if (FindUserInChannel(channel, userList[idx]) == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOTONCHANNEL, channel + ":You're not on that channel"));
        return;
    }
    std::string msgToPart = FormatMsg(userList[idx]);
    msgToPart.append(" PART " + channel + "\r\n");
    MessageToChannel(channelPool, channel, outputQueue, msgToPart);
    bool oper = userList[idx].joinChannelKeyPool[channel];
    
    std::vector<int>::iterator iter;
    for (iter = channelPool[channel].memberIdxPool.begin(); iter != channelPool[channel].memberIdxPool.end(); iter++)
    {
        if ((*iter) == userList[idx].fdPoolIdx)
        {
            break ;
        }
    }
    channelPool[channel].memberIdxPool.erase(iter);
    userList[idx].joinChannelKeyPool.erase(channel);
    if (channelPool[channel].memberIdxPool.size() == 0)
    {
        channelPool.erase(channel);
    }
    else if (oper)
    {
        int newOperIdx = FindUserById(channelPool[channel].memberIdxPool[0], userMaxNumber, userList);
        userList[newOperIdx].joinChannelKeyPool[channel] = true;
        std::vector<int>::iterator vIter = channelPool[channel].memberIdxPool.begin();
        for (; vIter != channelPool[channel].memberIdxPool.end(); vIter++)
        {
            PF_WHO((*vIter), channel, outputQueue);
        }
    }
}

void IRCCore::PF_KICK(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    ft::vector<std::string> arguments = Utils::split(msg, ' ');

    if (arguments.size() < 2)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, ":Not enough parameters"));
        return;
    }
    std::string channel = arguments.at(0);
    std::string userToKick = arguments.at(1);
    std::string comment;
    if (arguments.size() == 3)
        comment = arguments.at(2);
    else
        comment = userToKick + " is kicked in channel " + channel;
    int kickUserIdx = FindUserByNick(userToKick, userMaxNumber, userList);
    if (kickUserIdx == -1 || FindUserInChannel(channel, userList[kickUserIdx]) == false)
    {
        outputQueue->push(pollidx,  ErrorMsg(userList[idx], ERR_NOSUCHNICK, userToKick + ":No such nick", channel));
        return;
    }
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(channel);
    if (channelIter == channelPool.end())
    {
        outputQueue->push(pollidx,  ErrorMsg(userList[idx], ERR_NOSUCHCHANNEL, channel + ":No such channel"));
        return;  
    }
    if (FindUserInChannel(channel, userList[idx]) == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOTONCHANNEL, channel + ":You're not on that channel"));
        return;
    }
    if (userList[idx].joinChannelKeyPool[channel] == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_CHANOPRIVSNEEDED, channel + ":You're not channel operator", channel));
        return;
    }
    std::string msgToKick = FormatMsg(userList[idx]);
    msgToKick.append(" KICK " + channel + " " + userToKick + " :" + comment + "\r\n");
    MessageToChannel(channelPool, channel, outputQueue, msgToKick);
    bool oper = userList[idx].joinChannelKeyPool[channel];
    std::vector<int>::iterator iter;
    for (iter = channelPool[channel].memberIdxPool.begin(); iter != channelPool[channel].memberIdxPool.end(); iter++)
    {
        if ((*iter) == userList[kickUserIdx].fdPoolIdx)
        {
            break ;
        }
    }
    channelPool[channel].memberIdxPool.erase(iter);
    userList[kickUserIdx].joinChannelKeyPool.erase(channel);
    if (channelPool[channel].memberIdxPool.size() == 0)
    {
        channelPool.erase(channel);
    }
    else if (oper)
    {
        int newOperIdx = FindUserById(channelPool[channel].memberIdxPool[0], userMaxNumber, userList);
        userList[newOperIdx].joinChannelKeyPool[channel] = true;
        std::vector<int>::iterator vIter = channelPool[channel].memberIdxPool.begin();
        for (; vIter != channelPool[channel].memberIdxPool.end(); vIter++)
        {
            PF_WHO((*vIter), channel, outputQueue);
        }   
    }
}

void IRCCore::PF_PRIVMSG(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (msg == "")
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"));
        return ;
    }
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    if (arguments.size() == 2 && arguments[1] == "")
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOTEXTTOSEND, ":No text to send"));
        return ;
    }
    if (arguments[1][0] == ':')
    {
        arguments[1] = arguments[1].substr(1, arguments[1].length() -1);
    }
    std::string privMsg;
    for (int i = 1; i < arguments.size(); i++)
    {
        privMsg.append(arguments[i]);
        if (i == arguments.size() - 1)
        {
            break ;
        }
        privMsg.append(" ");
    }
    if (arguments[0][0] == '#')
    {
        std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(arguments[0]);
        if (channelIter == channelPool.end())
        {
            outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOSUCHCHANNEL, arguments[0] + ":No such channel"));
            return ;
        }
        std::vector<int>::iterator userIter = channelPool[arguments[0]].memberIdxPool.begin();
        for (; userIter != channelPool[arguments[0]].memberIdxPool.end(); userIter++)
        {
            if (*userIter != pollidx)
            {
                int recipientIdx = FindUserById(*userIter, userMaxNumber, userList);
                outputQueue->push(userList[recipientIdx].fdPoolIdx, CommandMsg(userList[idx], privMsg, arguments[0], "PRIVMSG"));
            }
        }
    }
    else
    {
        int recipientIdx = FindUserByNick(arguments[0], userMaxNumber, userList);
        if (recipientIdx == -1)
        {
            outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"));
            return ;
        }
        outputQueue->push(userList[recipientIdx].fdPoolIdx, CommandMsg(userList[idx], privMsg, userList[recipientIdx], "PRIVMSG"));
    }
}

void IRCCore::PF_NOTICE(int pollidx, std::string msg, CommQueue* outputQueue)
{
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    std::string noticeMsg;
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (arguments[1][0] == ':')
    {
        arguments[1] = arguments[1].substr(1, arguments[1].length() -1);
    }
    for (int i = 1; i < arguments.size(); i++)
    {
        noticeMsg.append(arguments[i]);
        if (i == arguments.size() - 1)
        {
            break ;
        }
        noticeMsg.append(" ");
    }
    if (arguments[0][0] == '#')
    {
        std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(arguments[0]);
        if (channelIter != channelPool.end())
        {
            std::vector<int>::iterator userIter = channelPool[arguments[0]].memberIdxPool.begin();
            for (; userIter != channelPool[arguments[0]].memberIdxPool.end(); userIter++)
            {
                if (*userIter != pollidx)
                {
                    int recipientIdx = FindUserById(*userIter, userMaxNumber, userList);
                    outputQueue->push(userList[recipientIdx].fdPoolIdx, CommandMsg(userList[idx], noticeMsg, arguments[0], "NOTICE"));
                }
            }
        }
    }
    else
    {
        int recipientIdx = FindUserByNick(arguments[0], userMaxNumber, userList);
        if (recipientIdx != -1)
        {
            outputQueue->push(userList[recipientIdx].fdPoolIdx, CommandMsg(userList[idx], noticeMsg, userList[recipientIdx], "NOTICE"));
        }
    }
}

void IRCCore::PF_NAME(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    std::string userNick = userList[idx].nick;
    std::string errMsg;
    if (msg == "")
    {
        errMsg = ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, "NAME :Not enough parameters");
        outputQueue->push(pollidx, errMsg);
        return ;
    }
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(msg);
    if (channelIter == channelPool.end())
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOSUCHCHANNEL, msg + ":No such channel"));
        return ;
    }
    std::string msgToName;
    std::vector<int>::iterator userIter = channelPool[msg].memberIdxPool.begin();
    std::vector<std::string> userNickList;
    for (; userIter != channelPool[msg].memberIdxPool.end(); userIter++)
    {
        idx = FindUserById(*userIter, userMaxNumber, userList);
        userNickList.push_back(userList[idx].nick);
    }
    msgToName.assign(":" + userList[idx].hostname + " " + RPL_NAMREPLY);
    msgToName.append(" " + userList[idx].nick + " = " + msg + " :");
    for (int i = 0; i < userNickList.size(); i++)
    {
        if (i != 0)
            msgToName.append(" ");
        msgToName.append(userNickList[i]);
    }
    msgToName.append("\r\n");
    outputQueue->push(pollidx, msgToName);
    msgToName.clear();
    msgToName = ReplyMsg(userList[idx], RPL_ENDOFNAMES, "End of NAMES list", msg);
    outputQueue->push(pollidx, msgToName);
}

void IRCCore::PF_WHO(int pollidx, std::string msg, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    std::string userNick = userList[idx].nick;
    std::string errMsg;
    if (msg == "")
    {
        errMsg = ErrorMsg(userList[idx], ERR_NEEDMOREPARAMS, "WHO :Not enough parameters");
        outputQueue->push(pollidx, errMsg);
        return ;
    }
    ft::vector<std::string> arguments = Utils::split(msg, ' ');
    std::map<std::string, Channel_t>::iterator channelIter = channelPool.find(arguments[0]);
    std::string msgToWho;
    if (channelIter == channelPool.end())
    {
        msgToWho = ReplyMsg(userList[idx], RPL_ENDOFWHO, arguments[0] + "End of /WHO list", "");
        outputQueue->push(pollidx, msgToWho);
        return ;
    }
    std::vector<int>::iterator userIter = channelPool[arguments[0]].memberIdxPool.begin();
    std::vector<std::string> userNickList;
    for (; userIter != channelPool[arguments[0]].memberIdxPool.end(); userIter++)
    {
        idx = FindUserById(*userIter, userMaxNumber, userList);
        if (userList[idx].joinChannelKeyPool[arguments[0]] == true)
            userNickList.push_back("@" + userList[idx].nick);
        else
            userNickList.push_back(userList[idx].nick);
    }
    msgToWho.assign(":");
    msgToWho.append(userList[idx].hostname);
    msgToWho.append(" ");
    msgToWho.append(RPL_NAMREPLY);
    msgToWho.append(" " + userList[idx].nick + " ");
    msgToWho.append("= ");
    msgToWho.append(arguments[0]);
    msgToWho.append(" :");
    for (int i = 0; i < userNickList.size(); i++)
    {
        if (i != 0)
            msgToWho.append(" ");
        msgToWho.append(userNickList[i]);
    }
    msgToWho.append("\r\n");
    outputQueue->push(pollidx, msgToWho);
    msgToWho.clear();
    msgToWho = ReplyMsg(userList[idx], RPL_ENDOFNAMES, "End of NAMES list", arguments[0]);
    outputQueue->push(pollidx, msgToWho);
}

bool IRCCore::PF_PNU(int pollidx, std::string keyCommand, CommQueue* outputQueue)
{
    int idx = FindUserById(pollidx, userMaxNumber, userList);
    if (keyCommand == "QUIT" && idx != -1) /* PASS ok user */
    {
        return true;
    }
    else if (keyCommand != "PASS" && idx == -1)
    {
        outputQueue->push(pollidx, ErrorMsg(ERR_NOAUTH, ":No Auth. Command [/PASS] to Connect"));
        return false;
    }
    else if (keyCommand != "NICK" && idx != -1 && userList[idx].bNick == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOSUCHNICK, ":Command /nick <nickname> first."));
        return false;
    }
    else if (keyCommand != "USER" && keyCommand != "NICK" && idx != -1 && userList[idx].bUser == false)
    {
        outputQueue->push(pollidx, ErrorMsg(userList[idx], ERR_NOUSER, ":Command [/USER <username> <hostname> <servername> <realname>]"));
        return false;
    }
    return true;
}