/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwonjimin <kwonjimin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:04:23 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/13 13:10:10 by kwonjimin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "ServDataStruct.hpp"
#include "Utils/NetSupportUtil.hpp"
#include "Utils/LogTool.hpp"
#include "Utils/CommQueue.hpp"
#include "NetCore/NetCore.hpp"
#include "IRCCore/IRCCore.hpp"

int main(int argc, char* argv[])
{
    ServerExecuteSpecification* executeSpecification;
    LogTool logCore;

    executeSpecification = Utils::ExtractExecuteArguments(argc, argv, &logCore);

    NetCore* netCore = new NetCore(&logCore);

    netCore->InitializeNetCore(executeSpecification);

    IRCCore* ircCore = new IRCCore();
    if (!ircCore->InitializeIRCCore(netCore->GetMaxFdSize(), executeSpecification->password,  &logCore))
    {
        logCore.WriteLog("Error: IRCCore initialzise fail.");
        return 1;
    }

    CommQueue inputQueue;
    CommQueue outputQueue;

    netCore->RunNetLoop(ircCore, &inputQueue, &outputQueue);

    netCore->DestroyNetCore();

    delete executeSpecification;
    delete netCore;
    delete ircCore;
    return 0;
}