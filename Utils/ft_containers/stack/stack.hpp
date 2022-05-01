/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:17:44 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/11/12 13:17:44 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
    template <class Type, class Container = ft::vector<Type> >
    class stack
    {
    public:
        typedef Container   container_type;
        typedef size_t      size_type;
        typedef Type        value_type;
    
    public:
        stack() {}
        stack(const container_type& copy)
        {
            dataPool = copy;
        }
        ~stack() {}

        bool empty() const
        {
            return dataPool.empty();
        }

        void pop()
        {
            if (!dataPool.empty())
                dataPool.erase(dataPool.begin() + (dataPool.size() - 1));
        }

        void push(const value_type& value)
        {
            dataPool.push_back(value);
        }

        size_type size() const
        {
            return dataPool.size();
        }

        value_type& top()
        {
            return dataPool[size() - 1];
        }
        const value_type& top() const
        {
            return dataPool[size() - 1];
        }
    
    private:
        friend bool operator==(const stack& left, const stack& right)
        {
            return left.dataPool == right.dataPool;
        }
        friend bool operator!=(const stack& left, const stack& right)
        {
            return left.dataPool != right.dataPool;
        }
        friend bool operator<(const stack& left, const stack& right)
        {
            return left.dataPool < right.dataPool;
        }
        friend bool operator<=(const stack& left, const stack& right)
        {
            return left.dataPool <= right.dataPool;
        }
        friend bool operator>(const stack& left, const stack& right)
        {
            return left.dataPool > right.dataPool;
        }
        friend bool operator>=(const stack& left, const stack& right)
        {
            return left.dataPool >= right.dataPool;
        }

    private:
        container_type dataPool;
    };

    template <class Type, class Container = ft::vector<Type> >
    bool operator==(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left == right;
    }
    template <class Type, class Container = ft::vector<Type> >
    bool operator!=(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left != right;
    }
    template <class Type, class Container = ft::vector<Type> >
    bool operator<(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left < right;
    }
    template <class Type, class Container = ft::vector<Type> >
    bool operator<=(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left <= right;
    }
    template <class Type, class Container = ft::vector<Type> >
    bool operator>(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left > right;
    }
    template <class Type, class Container = ft::vector<Type> >
    bool operator>=(const stack<Type, Container>& left, const stack<Type, Container>& right)
    {
        return left >= right;
    }
}

#endif