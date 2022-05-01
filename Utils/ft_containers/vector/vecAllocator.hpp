/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecAllocator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:09:17 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/10/05 13:45:59 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECALLOCATOR_HPP
#define VECALLOCATOR_HPP

#include <limits>

namespace ft
{
    template <class T>
    class vecAllocator
    {
    public:
        /*
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using void_pointer = void*;
        using const_void_pointer = const void*;
        using size_type = size_t;
        using defference_type = std::ptrdiff_t;
        */

        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef void* void_pointer;
        typedef const void* const_void_pointer;
        typedef size_t size_type;
        typedef std::ptrdiff_t defference_type;

    public:
        vecAllocator() {};
        template <typename U>
        vecAllocator(const vecAllocator<U>& other) { (void)other; }
        ~vecAllocator() {};

        template <typename U>
        struct rebind
        {
            // using other = vecAllocator<U>;
            typedef vecAllocator<U> other;
        };
        
        pointer allocate(size_type objectNum, const_void_pointer hint = NULL)
        {
            (void)hint;
            T* ret = new T[objectNum + 1];
            //ret[objectNum] = nullptr;
            return ret;
        }
        void deallocate(pointer ptr, size_type objectNum)
        {
            (void)objectNum;
            delete[] ptr;
        }

        size_t max_size() const
        {
            return std::numeric_limits<size_type>::max() / sizeof(value_type) - 1;
        }

        void construct(T* ptr, const T& ref) { *ptr = ref; }
        void destroy(T* ptr) { ptr->~T(); }
    };
}

#endif