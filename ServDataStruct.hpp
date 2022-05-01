/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServDataStruct.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:24:29 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:55:02 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <string>

struct ServerExecuteSpecification
{
    int port;
    std::string password;
};

#endif