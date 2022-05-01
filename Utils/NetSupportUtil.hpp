/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetSupportUtil.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:39:35 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:54:19 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETSUPPORTUTIL_HPP
#define NETSUPPORTUTIL_HPP

#include "../ServDataStruct.hpp"
#include "LogTool.hpp"
#include "ErrorHandling.hpp"
#include "ft_containers/vector/vector.hpp"

namespace Utils
{
    ServerExecuteSpecification* ExtractExecuteArguments(int argc, char* argv[], LogTool* logCore);
    ft::vector<std::string> split(std::string input, char delimiter);
};

#endif