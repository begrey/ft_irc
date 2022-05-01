/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandling.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwonjimin <kwonjimin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:39:25 by kwonjimin         #+#    #+#             */
/*   Updated: 2021/12/23 11:27:46 by kwonjimin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <string>
#include <errno.h>
#include "LogTool.hpp"

// if err == result of executing method, then print error and exit
template<typename T>
T ErrorHandle(T err, T res, std::string errorName, LogTool* logCore){
    if (res == err)
    {
        logCore->WriteLog(errorName);
        exit(1);
    } 
    return res;
}

template<typename T>
T ErrorHandleNotEqual(T err, T res, std::string errorName, LogTool* logCore){
    if (res != err)
    {
        logCore->WriteLog(errorName);
        exit(1);
    } 
    return res;
}

#endif
