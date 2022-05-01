/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommQueue.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:20 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:53:10 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMQUEUE_HPP
#define COMMQUEUE_HPP

#include <string>
#include <deque>
#include "./ft_containers/vector/vector.hpp"

struct QueueCell
{
    int pollIdx;
    std::string buffer;
};

class CommQueue
{
/* Functions */
public:
    CommQueue();
    ~CommQueue();

    void push(int pollIdx, std::string buffer);
    size_t size() const;          
    void pop();             /* remove first element */
    QueueCell front();      /* first element */

/* Variables */
public:
    std::deque<QueueCell> queueCell;
};

#endif