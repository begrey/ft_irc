/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:01:33 by jeongwle          #+#    #+#             */
/*   Updated: 2022/01/14 09:54:44 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
#define DEFINE_HPP

#define RPL_WELCOME "001"

#define RPL_ENDOFWHO "315"          // who 명령어 끝나고 출력 "<name> :End of /WHO list"
#define RPL_NOTOPIC "331"           // 토픽이 없으면 "<channel> :No topic is set"
#define RPL_TOPIC "332"             // 토픽이 있으면 "<channel> :<topic>"
#define RPL_WHOREPLY "352"
#define RPL_NAMREPLY "353"          // 뭔지 잘모르겠음 "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
#define RPL_ENDOFNAMES "366"
#define RPL_YOUREOPER "381"         // OPER권한을 얻었음을 클라이언트로 전송 ":You are now an IRC operator"
#define ERR_NOSUCHPASS "400"        // password불일치
#define ERR_NOSUCHNICK "401"        // 해당 닉네임 없음 "<nickname> :No such nick/channel"
#define ERR_NOSUCHCHANNEL "403"     // 채널 이름 잘못된 경우 "<channel name> :No such channel"
#define ERR_TOOMANYCHANNELS "405"   // 가입할 수 있는 채널 최대치를 넘겼을 경우 "<channel name> :You have joined too many channels"
#define ERR_NORECIPIENT "411"       // 수신인이 없는 경우 ":No recipient given (<command>)"
#define ERR_NOTEXTTOSEND "412"      // 보낼 메세지가 없는 경우 ":No text to send"
#define ERR_NONICKNAMEGIVEN "431"   // 닉네임 없을 시 ":No nickname given"
#define ERR_ERRONEUSNICKNAME "432"  // 정의되지 않은 문자가 닉네임으로 들어간 경우 "<nick> :Erroneus nickname"
#define ERR_NICKNAMEINUSE "433"     // 닉네임 중복 "<nick> :Nickname is already in use"
#define ERR_NOTONCHANNEL "442"      // 채널은 존재하나 JOIN된 채널이 아닐 경우 "<channel> :You're not on that channel"
#define ERR_NEEDMOREPARAMS "461"    // 파라미터 부족 "<command> :Not enough parameters"
#define ERR_ALREADYREGISTERED "462" // 이미등록된 것을 바꾸려 시도할 때 ":You may not reregister"
#define ERR_PASSWDMISMATCH "464"    // password가 요구되는 곳에서 password를 넘기지 않았거나 불일치 할 경우 ":Password incorrect"
#define ERR_BANNEDFROMCHAN "474"    // ban 당했을 경우 "<channel> :Cannot join channel (+b)"
#define ERR_BADCHANNELKEY "475"     // 잘못된 채널 키 "<channel> :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED "482"  // OPER가 아닌데 해당 명령어 사용할 경우 "<channel> :You're not channel operator"
#define ERR_NOOPERHOST "491"        // Operator 허용 거부할 경우 ":No O-lines for your host"

#define ERR_NOUSER "501" // 연결등록이 안됐을 때
#define ERR_NOAUTH "502" // password 입력하지 않은 경우
#define ERR_NICKTOOLONG "511" // nickname 길이 초과
#define ERR_CHANPREFIX "512" // channel prefix 에러, #로 시작해야함
#endif