/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommQueue.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwle <jeongwle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:02:20 by hyungyyo          #+#    #+#             */
/*   Updated: 2022/01/14 09:52:43 by jeongwle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommQueue.hpp"
#include <iostream>

CommQueue::CommQueue()
{
}
CommQueue::~CommQueue()
{
}

void CommQueue::push(int pollIdx, std::string buffer)
{
    QueueCell temp;
    temp.pollIdx = pollIdx;
    temp.buffer = buffer;
    this->queueCell.push_back(temp);
}

size_t CommQueue::size() const
{
    return this->queueCell.size();
}

void CommQueue::pop()
{
    this->queueCell.pop_front();
}

QueueCell CommQueue::front()
{
    return *(this->queueCell.begin());
}