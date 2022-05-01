/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:36:30 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/10/11 08:57:47 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECITERATOR_HPP
#define VECITERATOR_HPP

namespace ft
{
    template <typename T>
    class vecIterator
    {
    public:
        //using value_type = T;
        typedef T value_type;
        
    public:
        vecIterator(T* container_ = nullptr)
        {
            this->container = container_;
        }

        vecIterator<T>& operator++(int)
        {
            container++;
            return *this;
        }
        vecIterator<T>& operator++()
        {
            container++;
            return *this;
        }
        vecIterator<T>& operator--(int)
        {
            container--;
            return *this;
        }
        vecIterator<T>& operator--()
        {
            container--;
            return *this;
        }
        vecIterator<T> operator+(const int operand)
        {
            //container += operand;
            return vecIterator<T>(container + operand);
            //return *this;
        }
        vecIterator<T> operator-(const int operand)
        {
            //container -= operand;
            return vecIterator<T>(container - operand);
            //return *this;
        }
        T& operator*() { return *container; }
        bool operator==(const vecIterator& operand) { return container == operand.container; }
        bool operator!=(const vecIterator& operand) { return container != operand.container; }
    
    private:
        T* container;
    };

    template <typename T>
    class vecConstIterator
    {
    public:
        //using value_type = T;
        typedef T value_type;
        
    public:
        vecConstIterator(T* container_ = nullptr)
        {
            this->container = container_;
        }

        vecConstIterator<T> operator+(const int operand)
        {
            //container += operand;
            return vecConstIterator<T>(container + operand);
            //return *this;
        }
        vecConstIterator<T> operator-(const int operand)
        {
            //container -= operand;
            return vecConstIterator<T>(container - operand);
            //return *this;
        }
        T& operator*() { return (*container); }
        bool operator==(const ft::vecIterator<T>& operand) { return container == operand.container; }
        bool operator!=(const ft::vecIterator<T>& operand) { return container != operand.container; }
        bool operator==(const ft::vecConstIterator<T>& operand) { return container == operand.container; }
        bool operator!=(const ft::vecConstIterator<T>& operand) { return container != operand.container; }
    
    private:
        T* container;
    };

    template <typename T>
    class vecReverseIterator
    {
    public:
        //using value_type = T;
        typedef T value_type;
        
    public:
        vecReverseIterator(T* container_ = nullptr)
        {
            this->container = container_;
        }

        vecReverseIterator<T>& operator++(int)
        {
            container--;
            return *this;
        }
        T& operator*() { return *container; }
        bool operator==(const vecReverseIterator& operand) { return container == operand.container; }
        bool operator!=(const vecReverseIterator& operand) { return container != operand.container; }

    private:
        T* container;
    };

    template <typename T>
    class vecConstReverseIterator
    {
    public:
        //using value_type = T;
        typedef T value_type;
        
    public:
        vecConstReverseIterator(T* container_ = nullptr)
        {
            this->container = container_;
        }

        vecConstReverseIterator<T>& operator++(int)
        {
            container--;
            return *this;
        }
        T& operator*() { return *container; }
        bool operator==(const vecReverseIterator<T>& operand) { return container == operand.container; }
        bool operator!=(const vecReverseIterator<T>& operand) { return container != operand.container; }
        bool operator==(const vecConstReverseIterator& operand) { return container == operand.container; }
        bool operator!=(const vecConstReverseIterator& operand) { return container != operand.container; }

    private:
        T* container;
    };
}

#endif