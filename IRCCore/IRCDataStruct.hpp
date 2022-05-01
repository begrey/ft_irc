/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCDataStruct.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:20 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:50:06 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCDATASTRUCT_HPP
#define IRCDATASTRUCT_HPP

#include <string>
#include <vector>
#include "../Utils/ft_containers/vector/vector.hpp"

struct User_t
{
    bool bFill;
    bool bAuth;
    bool bUser;
    bool bNick;

    int fdPoolIdx;
    std::string nick;
    std::string hostname;
    std::string user;
    std::map<std::string, bool> joinChannelKeyPool;
};

struct Channel_t
{
    std::string topic;
    int userNumber;
    std::vector<int> memberIdxPool;
    bool bFill;
    std::string key; // ? 채팅방 비번
};

#endif