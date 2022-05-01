/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetSupportUtil.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwonjimin <kwonjimin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 20:54:19 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/12/27 17:04:50 by kwonjimin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetSupportUtil.hpp"

bool portChecker(int port)
{
    if (port < 1024 || port > 49151)
    {
        return false;
    }
    return true;
}

ServerExecuteSpecification* Utils::ExtractExecuteArguments(int argc, char* argv[], LogTool* logCore)
{
    ErrorHandleNotEqual(3, argc, "Argument Error: arguments form most includes \'[host:port_network:password_network] <port> <password>\' or \'<port> <password>\'.", logCore);

    std::stringstream ssInt;
    int port;

    ssInt << std::string(argv[1]);
    ssInt >> port;
    ErrorHandle(false, portChecker(port), "Argument Error: Wrong port.", logCore);

    ServerExecuteSpecification* executeSpecification = new ServerExecuteSpecification;

    // B, C case (<port> <password> only)
    
    executeSpecification->port = port;
    executeSpecification->password = std::string(argv[2]);

    logCore->WriteLog("Server execution specification read succeed.");
    std::string logStr;
    logStr = " > port: " + std::string(argv[1]);
    logCore->WriteLog(logStr);
    logStr = " > password: " + executeSpecification->password;
    logCore->WriteLog(logStr);

    return executeSpecification;
}

ft::vector<std::string> Utils::split(std::string input, char delimiter) {
    ft::vector<std::string> answer;
    std::stringstream ss(input);
    std::string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}