/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorUtil.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 20:53:35 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/12/17 20:53:35 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGTOOL_HPP
#define LOGTOOL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class LogTool
{
public:
    LogTool();
    ~LogTool();

    size_t WriteLog(std::string logStr);
    
    void FatalError(std::string errorStr);

private:
    std::fstream logFile;
    unsigned int logNum;
};

#endif