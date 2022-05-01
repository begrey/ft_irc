/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCSupportUtil.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:15:16 by kwonjimin         #+#    #+#             */
/*   Updated: 2022/01/14 10:54:34 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSUPPORTUTIL_HPP
#define IRCSUPPORTUTIL_HPP

std::string FormatMsg(User_t user)
{
    std::string msg;
    msg.assign(":");
    msg.append(user.nick);
    msg.append("!");
    msg.append(user.user);
    msg.append("@");
    msg.append(user.hostname);
    return msg;
}

std::string ReplyMsg(User_t user, std::string reply, std::string content, std::string channel)
{
    std::string msg;
    msg.assign(":");
    msg.append(user.hostname);
    msg.append(" ");
    msg.append(reply);
    msg.append(" ");
    msg.append(user.nick);
    msg.append(" ");
    if (channel != "")
    {
        msg.append(channel);
        msg.append(" ");
    }
    msg.append(content);
    msg.append("\r\n");
    return msg;
}

std::string ErrorMsg(User_t user, std::string error, std::string content, std::string channel) 
{
    std::string msg;
    msg.assign(":");
    msg.append(user.hostname);
    msg.append(" ");
    msg.append(error);
    msg.append(" ");
    if (user.nick == "")
        msg.append("*");
    else
        msg.append(user.nick);
    msg.append(" ");
    msg.append(channel);
    msg.append(" ");
    msg.append(content);
    msg.append("\r\n");
    return msg;
}

std::string ErrorMsg(User_t user, std::string error, std::string content) 
{
    std::string msg;
    msg.assign(":");
    msg.append(user.hostname);
    msg.append(" ");
    msg.append(error);
    msg.append(" ");
    if (user.nick == "")
        msg.append("*");
    else
        msg.append(user.nick);
    msg.append(" ");
    msg.append(content);
    msg.append("\r\n");
    return msg;
}

std::string ErrorMsg(std::string error, std::string content)
{
    std::string msg;
    msg.assign(":");
    msg.append(" ");
    msg.append(error);
    msg.append(" * ");
    msg.append(content);
    msg.append("\r\n");
    return msg;
}

std::string CommandMsg(User_t user, std::string message, std::string channel, std::string command)
{
    std::string msg;
    msg = FormatMsg(user);
    msg.append(" ");
    msg.append(command);
    msg.append(" ");
    if (channel != "")
    {
        msg.append(channel);
        msg.append(" ");
    }
    msg.append(message);
    msg.append("\r\n");
    return msg;
}

std::string CommandMsg(User_t user, std::string message, User_t recipient, std::string command)
{
    std::string msg;
    msg = FormatMsg(user);
    msg.append(" ");
    msg.append(command);
    msg.append(" ");
    msg.append(recipient.nick);
    msg.append(" ");
    msg.append(":");
    msg.append(message);
    msg.append("\r\n");
    return msg;
}

bool CheckNickname(std::string nickname)
{
    for (int i = 0; i < nickname.length(); i++)
    {
        if (nickname[i] < 33 || nickname[i] > 126)
            return false;
    }
    return true;
}

Channel_t InitChannel()
{
    Channel_t channel;
    channel.topic = "";
    channel.userNumber = 1;
    channel.bFill = true;
    channel.key = ""; 

    return channel;
}

int FindUserById(int pollIdx, int userNum, User_t *userList)
{
    for (int i = 0; i < userNum; i++) 
    {
        if (userList[i].fdPoolIdx == pollIdx)
        {
            return i;
        }
    }
    return -1;
}

bool CheckChannelName(std::string channel)
{
    if ( channel == "" || channel.front() != '#' ||
            channel.find(" ") != std::string::npos)
    {
        return false;
    }
    return true;
}

bool FindUserInChannel(std::string channelName, User_t user)
{

    std::map<std::string, bool>::iterator channelIter;
    for (channelIter = user.joinChannelKeyPool.begin(); channelIter != user.joinChannelKeyPool.end(); channelIter++)
    {
        if ((*channelIter).first == channelName)
            return true;
    }
    return false;
    
}

int FindUserByNick(std::string nickname, int userNum, User_t *userList)
{
     for (int i = 0; i < userNum; i++) 
    {
        if (userList[i].nick == nickname)
        {
            return i;
        }
    }
    return -1;
}

void MessageToChannel(std::map<std::string, Channel_t> channelPool, std::string channelName, CommQueue* outputQueue, std::string msg)
{
    Channel_t channel = channelPool[channelName];
    std::vector<int>::iterator iter;

    for (iter = channel.memberIdxPool.begin(); iter != channel.memberIdxPool.end(); iter++)
    {
        outputQueue->push((*iter), msg);
    }
}

#endif
