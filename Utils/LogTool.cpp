/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogTool.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwonjimin <kwonjimin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:04:56 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/12/23 11:27:44 by kwonjimin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LogTool.hpp"

LogTool::LogTool()
{
    logFile.open("IRCServLog.txt", std::ios::app);
    if (logFile.is_open())
    {
        logNum = 0;
        logFile << "-----LogTool initialized, log start.-----" << std::endl;
    }
    else
    {
        std::cout << "Error: LogTool initilaize fail" << std::endl;
    }
}
LogTool::~LogTool()
{
    if (logFile.is_open())
    {
        logFile << "-----LogTool destroyed, log end.-----" << std::endl << std::endl << std::endl;
        logFile.close();
    }
}

size_t LogTool::WriteLog(std::string logStr)
{
    std::stringstream convIntToStrStream;
    convIntToStrStream << logNum;
    std::string logNumStr = convIntToStrStream.str();

    for (int i = logNumStr.length(); i < 7; i++)
    {
        logNumStr = logNumStr + " ";
    }
    logNumStr = logNumStr + "| ";

    if (logFile.is_open())
    {
        logFile << logNumStr;
        logFile << logStr << std::endl;
    }
    std::cout << logNumStr << logStr << std::endl;
    logNum++;

    return logNumStr.length() + logStr.length();
}

void LogTool::FatalError(std::string errorStr)
{
    if (logFile.is_open())
    {
        logFile << "!!!---Fatal Error---!!!" << std::endl;
        logFile << ": " << errorStr << std::endl << std::endl << std::endl;

        logFile.close();
    }
    std::cout << "!!!---Fatal Error---!!!" << std::endl;
    std::cout << ": " << errorStr << std::endl;
    logNum++;

    exit(1);
}