/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:45:47 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/10/11 09:04:37 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include "vecAllocator.hpp"
#include "vecIterator.hpp"

namespace ft
{
    // vector template class
    template <class Type, class Allocator = vecAllocator<Type> >
    class vector
    {
    public:
        /*
        * Typedef
        */
        typedef vecIterator<Type>               iterator;
        typedef vecConstIterator<Type>          const_iterator;
        typedef vecReverseIterator<Type>        reverse_iterator;
        typedef vecConstReverseIterator<Type>   const_reverse_iterator;

        typedef Type value_type;
        typedef Type* pointer;
        typedef const Type* const_pointer;
        typedef Type& reference;
        typedef const Type& const_reference;
        typedef void* void_pointer;
        typedef const void* const_void_pointer;
        typedef size_t size_type;
        typedef std::ptrdiff_t defference_type;

    private:
        /*
        * Variable
        */
        Type*       dataPool;
        size_t      allocSize;
        size_t      fillSize;
        Allocator   alloc;

    public:
        /*
        * Constructor, Destructor
        */
        vector(const Allocator& allocator = Allocator())
        {
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            alloc = allocator;
        }
        vector(size_type count, const Type& value = Type(), const Allocator& allocator = Allocator())
        {
            alloc = allocator;
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (count != 0 && max_size() > count)
            {
                dataPool = alloc.allocate(count);
                allocSize = count;
                fillSize = count;
                for (size_type i = 0; i < count; i++)
                {
                    dataPool[i] = value;
                }
            }
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const Allocator& allocator = Allocator())
        {
            alloc = allocator;
            
            size_type iterator_size = 0;
            for (InputIterator temp_first = first; temp_first != last; temp_first++)
            {
                iterator_size++;
            }

            if (iterator_size == 0 || iterator_size > max_size())
            {
                dataPool = nullptr;
                allocSize = 0;
                fillSize = 0;
                return;
            }

            allocSize = iterator_size;
            fillSize = iterator_size;
            dataPool = alloc.allocate(fillSize);
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(*first);
                first++;
            }
        }
        vector(const vector& source)
        {
            alloc = Allocator();
            allocSize = source.size();
            fillSize = source.size();
            dataPool = nullptr;
            if (allocSize != 0)
            {
                dataPool = alloc.allocate(allocSize);
            }
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(source[i]);
            }
        }
        ~vector()
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
                dataPool = nullptr;
            }
        }

        /*
        * Member function
        */
        void assign(size_type count, const Type& value)
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (count != 0 && count < max_size())
            {
                dataPool = alloc.allocate(count);
                allocSize = count;
                fillSize = count;

                for (int i = 0; i < count; i++)
                {
                    dataPool[i] = value;
                }
            }
        }
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            size_type iter_size = 0;
            for (InputIterator temp_first = first; temp_first != last; temp_first++)
            {
                iter_size++;
            }

            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (iter_size != 0 && iter_size < max_size())
            {
                dataPool = alloc.allocate(iter_size);
                allocSize = iter_size;
                fillSize = iter_size;

                for (int i = 0; i < fillSize; i++)
                {
                    dataPool[i] = *first;
                    first++;
                }
            }
        }

        reference at(size_type position)
        {
            if (position >= fillSize)
            {
                throw std::out_of_range("ft::vector -> Out of range exception!");
            }
            
            return dataPool[position];
        }
        const_reference at(size_type position) const
        {
            if (position >= fillSize)
            {
                throw std::out_of_range("ft::vector -> Out of range exception!");
            }
            
            return dataPool[position];
        }

        reference front()
        {
            return dataPool[0];
        }
        const_reference front() const
        {
            return dataPool[0];
        }
        reference back()
        {
            return dataPool[fillSize - 1];
        }
        const_reference back() const
        {
            return dataPool[fillSize - 1];
        }

        iterator begin()
        {
            return vecIterator<Type>(dataPool);
        }
        const_iterator begin() const
        {
            return vecIterator<Type>(dataPool);
        }
        iterator end()
        {
            return vecIterator<Type>(dataPool + allocSize);
        }
        const_iterator end() const
        {
            return vecIterator<Type>(dataPool + allocSize);
        }

        reverse_iterator rbegin()
        {
            return vecReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        const_reverse_iterator rbegin() const
        {
            return vecReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        reverse_iterator rend()
        {
            return vecReverseIterator<Type>(dataPool - 1);
        }
        const_reverse_iterator rend() const
        {
            return vecReverseIterator<Type>(dataPool - 1);
        }

        const_iterator cbegin() const
        {
            return vecIterator<Type>(dataPool);
        }
        const_iterator cend() const
        {
            return vecIterator<Type>(dataPool + allocSize);
        }

        const_reverse_iterator crbegin() const
        {
            return vecReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        const_reverse_iterator crend() const
        {
            return vecReverseIterator<Type>(dataPool - 1);
        }

        size_type capacity() const
        {
            return allocSize;
        }

        void clear()
        {
            fillSize = 0;
        }

        pointer data()
        {
            return dataPool;
        }
        const_pointer data() const
        {
            return dataPool;
        }

        bool empty() const
        {
            if (fillSize == 0)
            {
                return true;
            }
            return false;
        }

        iterator erase(iterator position)
        {
            for (int i = 0; i < fillSize; i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    fillSize--;
                    for (int ii = i; ii < fillSize; ii++)
                    {
                        dataPool[ii] = dataPool[i + 1];
                    }
                    return vecIterator<Type>(dataPool + i);
                }
            }
            return vecIterator<Type>(nullptr);
        }
        iterator erase(iterator first, iterator last)
        {
            iterator ret = vecIterator<Type>(nullptr);
            
            for (first; first != last; first++)
            {
                for (int i = 0; i < fillSize; i++)
                {
                    if (first == vecIterator<Type>(dataPool + i))
                    {
                        fillSize--;
                        for (int ii = i; ii < fillSize; ii++)
                        {
                            dataPool[ii] = dataPool[ii + 1];
                        }
                        ret = vecIterator<Type>(dataPool + i);
                    }
                }
            }
            return ret;
        }

        Allocator get_allocator() const
        {
            return alloc;
        }

        iterator insert(iterator position, const Type& value)
        {
            for (int i = 0; i < fillSize; i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    if (fillSize + 1 > allocSize)
                    {
                        ft::vector<Type> copy;
                        if (dataPool != nullptr)
                        {
                            copy = ft::vector<Type>(*this);
                            alloc.deallocate(dataPool, allocSize);
                        }
                        fillSize += 1;
                        allocSize *= 2;
                        if (allocSize == 0)
                        {
                            allocSize = 1;
                        }
                        dataPool = alloc.allocate(allocSize);

                        bool bj = false;
                        for (int ii = 0; ii < fillSize; ii++)
                        {
                            if (ii == i)
                            {
                                bj = true;
                            }
                            if (copy.size() != 0)
                            {
                                dataPool[ii + static_cast<int>(bj)] = copy[ii];
                            }
                            else
                            {
                                dataPool[ii + static_cast<int>(bj)] = Type();
                            }
                        }
                        dataPool[i] = value;
                    }
                    else
                    {
                        fillSize++;
                        for (int ii = fillSize - 1; ii > i; ii--)
                        {
                            dataPool[ii] = dataPool[ii - i];
                        }
                        dataPool[i] = value;
                    }
                    return vecIterator<Type>(dataPool + i);
                }
            }
            return vecIterator<Type>(nullptr);
        }
        void insert(iterator position, size_type count, const Type& value)
        {
            if (count == 0) { return; }

            int insertPos = -1;
            for (int i = 0; i < size(); i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    insertPos = i;
                    break;
                }
            }
            if (insertPos != -1)
            {
                for (int i = 0; i < count; i++)
                {
                    insert(begin() + insertPos, value);
                }
            }
        }
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            int insertPos = -1;
            for (int i = 0; i < size(); i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    insertPos = i;
                    break;
                }
            }
            if (insertPos != -1)
            {
                /*for (; first != last; first++)
                {
                    insert(begin() + insertPos, *first);
                    //insertPos += 1;
                }*/
                last--;
                first--;
                for (; last != first; last--)
                {
                    insert(begin() + insertPos, *last);
                }
            }
        }

        size_type max_size() const
        {
            return alloc.max_size();
        }

        void pop_back()
        {
            if (fillSize != 0)
            {
                fillSize -= 1;
            }
        }

        void push_back(const Type& value)
        {
            if (fillSize + 1 > allocSize)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                fillSize += 1;
                allocSize *= 2;
                if (allocSize == 0)
                {
                    allocSize = 1;
                }
                dataPool = alloc.allocate(allocSize);

                for (int i = 0; i < size() - 1; i++)
                {
                    dataPool[i] = copy[i];
                }
                dataPool[size() - 1] = value;

                return;
            }
            fillSize += 1;
            dataPool[size() - 1] = value;
        }

        void reserve(size_type count)
        {
            if (count > allocSize && count != 0)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = count;
                dataPool = alloc.allocate(allocSize);

                if (copy.size() != 0)
                {
                    for (int i = 0; i < size() - 1; i++)
                    {
                        dataPool[i] = copy[i];
                    }
                }
            }
        }

        void resize(size_type new_size, Type value = Type())
        {
            if (new_size <= fillSize) { return; }
            if (new_size <= allocSize)
            {
                int oldSize = fillSize - 1;
                fillSize = new_size;
                for (; oldSize < fillSize; oldSize++)
                {
                    dataPool[oldSize] = value;
                }
            }
            else
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = new_size * 2;
                int oldSize = fillSize;
                fillSize = new_size;
                dataPool = alloc.allocate(allocSize);

                for (int i = 0; i < fillSize; i++)
                {
                    if (i < oldSize)
                    {
                        dataPool[i] = copy[i];
                    }
                    else
                    {
                        dataPool[i] = value;
                    }
                }
            }
        }

        void shrink_to_fit()
        {
            if (fillSize != allocSize)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = fillSize;
                dataPool = alloc.allocate(allocSize);
                
                for (int i = 0; i < copy.size(); i++)
                {
                    dataPool[i] = copy[i];
                }
            }
        }

        size_type size() const
        {
            return fillSize;
        }

        void swap(vector<Type, Allocator>& right)
        {
            Type* tempDataPool = dataPool;
            size_t tempAllocSize = allocSize;
            size_t tempFillSize = fillSize;
            dataPool = right.dataPool;
            allocSize = right.allocSize;
            fillSize = right.fillSize;
            
            right.dataPool = tempDataPool;
            right.allocSize = tempAllocSize;
            right.fillSize = tempFillSize;
        }

        // operator
        reference operator[](size_type position)
        {
            return dataPool[position];
        }
        const_reference operator[](size_type position) const
        {
            return dataPool[position];
        }
        vector& operator=(const vector& right)
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            allocSize = right.size();
            fillSize = right.size();
            dataPool = nullptr;
            if (allocSize != 0)
            {
                dataPool = alloc.allocate(allocSize);
            }
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(right[i]);
            }
            return *this;
        }
    };

    template <class Allocator>
    class vector<bool, Allocator>
    {
    public:
        /*
        * Typedef
        */
        typedef bool                            Type;
        typedef vecIterator<Type>               iterator;
        typedef vecConstIterator<Type>         const_iterator;
        typedef vecReverseIterator<Type>        reverse_iterator;
        typedef vecConstReverseIterator<Type>  const_reverse_iterator;

        typedef Type value_type;
        typedef Type* pointer;
        typedef const Type* const_pointer;
        typedef Type& reference;
        typedef const Type& const_reference;
        typedef void* void_pointer;
        typedef const void* const_void_pointer;
        typedef size_t size_type;
        typedef std::ptrdiff_t defference_type;

    private:
        /*
        * Variable
        */
        Type*       dataPool;
        size_t      allocSize;
        size_t      fillSize;
        Allocator   alloc;

    public:
        /*
        * Constructor, Destructor
        */
        vector(const Allocator& allocator = Allocator())
        {
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            alloc = allocator;
        }
        vector(size_type count, const Type& value = Type(), const Allocator& allocator = Allocator())
        {
            alloc = allocator;
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (count != 0 && max_size() > count)
            {
                dataPool = alloc.allocate(count);
                allocSize = count;
                fillSize = count;
                for (size_type i = 0; i < count; i++)
                {
                    dataPool[i] = value;
                }
            }
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const Allocator& allocator = Allocator())
        {
            alloc = allocator;
            
            size_type iterator_size = 0;
            for (InputIterator temp_first = first; temp_first != last; temp_first++)
            {
                iterator_size++;
            }

            if (iterator_size == 0 || iterator_size > max_size())
            {
                dataPool = nullptr;
                allocSize = 0;
                fillSize = 0;
                return;
            }

            allocSize = iterator_size;
            fillSize = iterator_size;
            dataPool = alloc.allocate(fillSize);
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(*first);
                first++;
            }
        }
        vector(const vector& source)
        {
            alloc = Allocator();
            allocSize = source.size();
            fillSize = source.size();
            dataPool = nullptr;
            if (allocSize != 0)
            {
                dataPool = alloc.allocate(allocSize);
            }
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(source[i]);
            }
        }
        ~vector()
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
                dataPool = nullptr;
            }
        }

        /*
        * Member function
        */
        void assign(size_type count, const Type& value)
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (count != 0 && count < max_size())
            {
                dataPool = alloc.allocate(count);
                allocSize = count;
                fillSize = count;

                for (int i = 0; i < count; i++)
                {
                    dataPool[i] = value;
                }
            }
        }
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            size_type iter_size = 0;
            for (InputIterator temp_first = first; temp_first != last; temp_first++)
            {
                iter_size++;
            }

            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            dataPool = nullptr;
            allocSize = 0;
            fillSize = 0;
            if (iter_size != 0 && iter_size < max_size())
            {
                dataPool = alloc.allocate(iter_size);
                allocSize = iter_size;
                fillSize = iter_size;

                for (int i = 0; i < fillSize; i++)
                {
                    dataPool[i] = *first;
                    first++;
                }
            }
        }

        reference at(size_type position)
        {
            if (position >= fillSize)
            {
                throw std::out_of_range("ft::vector -> Out of range exception!");
            }
            
            return dataPool[position];
        }
        const_reference at(size_type position) const
        {
            if (position >= fillSize)
            {
                throw std::out_of_range("ft::vector -> Out of range exception!");
            }
            
            return dataPool[position];
        }

        reference front()
        {
            return dataPool[0];
        }
        const_reference front() const
        {
            return dataPool[0];
        }
        reference back()
        {
            return dataPool[fillSize - 1];
        }
        const_reference back() const
        {
            return dataPool[fillSize - 1];
        }

        iterator begin()
        {
            return vecIterator<Type>(dataPool);
        }
        const_iterator begin() const
        {
            return vecConstIterator<Type>(dataPool);
        }
        iterator end()
        {
            return vecIterator<Type>(dataPool + allocSize);
        }
        const_iterator end() const
        {
            return vecConstIterator<Type>(dataPool + allocSize);
        }

        reverse_iterator rbegin()
        {
            return vecReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        const_reverse_iterator rbegin() const
        {
            return vecConstReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        reverse_iterator rend()
        {
            return vecReverseIterator<Type>(dataPool - 1);
        }
        const_reverse_iterator rend() const
        {
            return vecConstReverseIterator<Type>(dataPool - 1);
        }

        const_iterator cbegin() const
        {
            return vecConstIterator<Type>(dataPool);
        }
        const_iterator cend() const
        {
            return vecConstIterator<Type>(dataPool + allocSize);
        }

        const_reverse_iterator crbegin() const
        {
            return vecConstReverseIterator<Type>(dataPool + (allocSize - 1));
        }
        const_reverse_iterator crend() const
        {
            return vecConstReverseIterator<Type>(dataPool - 1);
        }

        size_type capacity() const
        {
            return allocSize;
        }

        void clear()
        {
            fillSize = 0;
        }

        pointer data()
        {
            return dataPool;
        }
        const_pointer data() const
        {
            return dataPool;
        }

        bool empty() const
        {
            if (fillSize == 0)
            {
                return true;
            }
            return false;
        }

        iterator erase(const_iterator position)
        {
            for (int i = 0; i < fillSize; i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    fillSize--;
                    for (int ii = i; ii < fillSize; ii++)
                    {
                        dataPool[ii] = dataPool[i + 1];
                    }
                    return vecIterator<Type>(dataPool + i);
                }
            }
            return vecIterator<Type>(nullptr);
        }
        iterator erase(iterator first, iterator last)
        {
            iterator ret = vecIterator<Type>(nullptr);
            
            for (; first != last; first++)
            {
                for (int i = 0; i < fillSize; i++)
                {
                    if (first == vecIterator<Type>(dataPool + i))
                    {
                        fillSize--;
                        for (int ii = i; ii < fillSize; ii++)
                        {
                            dataPool[ii] = dataPool[ii + 1];
                        }
                        ret = vecIterator<Type>(dataPool + i);
                    }
                }
            }
            return ret;
        }

        Allocator get_allocator() const
        {
            return alloc;
        }

        iterator insert(iterator position, const Type& value)
        {
            for (int i = 0; i < fillSize; i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    if (fillSize + 1 > allocSize)
                    {
                        ft::vector<Type> copy;
                        if (dataPool != nullptr)
                        {
                            copy = ft::vector<Type>(*this);
                            alloc.deallocate(dataPool, allocSize);
                        }
                        fillSize += 1;
                        allocSize *= 2;
                        if (allocSize == 0)
                        {
                            allocSize = 1;
                        }
                        dataPool = alloc.allocate(allocSize);

                        bool bj = false;
                        for (int ii = 0; ii < fillSize; ii++)
                        {
                            if (ii == i)
                            {
                                bj = true;
                            }
                            if (copy.size() != 0)
                            {
                                dataPool[ii + static_cast<int>(bj)] = copy[ii];
                            }
                            else
                            {
                                dataPool[ii + static_cast<int>(bj)] = Type();
                            }
                        }
                        dataPool[i] = value;
                    }
                    else
                    {
                        fillSize++;
                        for (int ii = fillSize - 1; ii > i; ii--)
                        {
                            dataPool[ii] = dataPool[ii - i];
                        }
                        dataPool[i] = value;
                    }
                    return vecIterator<Type>(dataPool + i);
                }
            }
            return vecIterator<Type>(nullptr);
        }
        void insert(iterator position, size_type count, const Type& value)
        {
            if (count == 0) { return; }

            int insertPos = -1;
            for (int i = 0; i < size(); i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    insertPos = i;
                    break;
                }
            }
            if (insertPos != -1)
            {
                for (int i = 0; i < count; i++)
                {
                    insert(begin() + insertPos, value);
                }
            }
        }
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            int insertPos = -1;
            for (int i = 0; i < size(); i++)
            {
                if (position == vecIterator<Type>(dataPool + i))
                {
                    insertPos = i;
                    break;
                }
            }
            if (insertPos != -1)
            {
                /*for (; first != last; first++)
                {
                    insert(begin() + insertPos, *first);
                    //insertPos += 1;
                }*/
                last--;
                first--;
                for (; last != first; last--)
                {
                    insert(begin() + insertPos, *last);
                }
            }
        }

        size_type max_size() const
        {
            return alloc.max_size();
        }

        void pop_back()
        {
            if (fillSize != 0)
            {
                fillSize -= 1;
            }
        }

        void push_back(const Type& value)
        {
            if (fillSize + 1 > allocSize)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                fillSize += 1;
                allocSize *= 2;
                if (allocSize == 0)
                {
                    allocSize = 1;
                }
                dataPool = alloc.allocate(allocSize);

                for (int i = 0; i < size() - 1; i++)
                {
                    dataPool[i] = copy[i];
                }
                dataPool[size() - 1] = value;

                return;
            }
            fillSize += 1;
            dataPool[size() - 1] = value;
        }

        void reserve(size_type count)
        {
            if (count > allocSize && count != 0)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = count;
                dataPool = alloc.allocate(allocSize);

                if (copy.size() != 0)
                {
                    for (int i = 0; i < size() - 1; i++)
                    {
                        dataPool[i] = copy[i];
                    }
                }
            }
        }

        void resize(size_type new_size, Type value = Type())
        {
            if (new_size <= fillSize) { return; }
            if (new_size <= allocSize)
            {
                int oldSize = fillSize - 1;
                fillSize = new_size;
                for (; oldSize < fillSize; oldSize++)
                {
                    dataPool[oldSize] = value;
                }
            }
            else
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = new_size * 2;
                int oldSize = fillSize;
                fillSize = new_size;
                dataPool = alloc.allocate(allocSize);

                for (int i = 0; i < fillSize; i++)
                {
                    if (i < oldSize)
                    {
                        dataPool[i] = copy[i];
                    }
                    else
                    {
                        dataPool[i] = value;
                    }
                }
            }
        }

        void shrink_to_fit()
        {
            if (fillSize != allocSize)
            {
                ft::vector<Type> copy;
                if (dataPool != nullptr)
                {
                    copy = ft::vector<Type>(*this);
                    alloc.deallocate(dataPool, allocSize);
                }
                allocSize = fillSize;
                dataPool = alloc.allocate(allocSize);
                
                for (int i = 0; i < copy.size(); i++)
                {
                    dataPool[i] = copy[i];
                }
            }
        }

        size_type size() const
        {
            return fillSize;
        }

        void swap(vector<Type, Allocator>& right)
        {
            Type* tempDataPool = dataPool;
            size_t tempAllocSize = allocSize;
            size_t tempFillSize = fillSize;
            dataPool = right.dataPool;
            allocSize = right.allocSize;
            fillSize = right.fillSize;
            
            right.dataPool = tempDataPool;
            right.allocSize = tempAllocSize;
            right.fillSize = tempFillSize;
        }

        void flip()
        {
            for (int i = 0; i < size(); i++)
            {
                dataPool[i] = !dataPool[i];
            }
        }

        // operator
        reference operator[](size_type position)
        {
            return dataPool[position];
        }
        const_reference operator[](size_type position) const
        {
            return dataPool[position];
        }
        vector& operator=(const vector& right)
        {
            if (dataPool != nullptr)
            {
                alloc.deallocate(dataPool, allocSize);
            }
            allocSize = right.size();
            fillSize = right.size();
            dataPool = nullptr;
            if (allocSize != 0)
            {
                dataPool = alloc.allocate(allocSize);
            }
            for (int i = 0; i < fillSize; i++)
            {
                dataPool[i] = Type(right[i]);
            }
            return *this;
        }
    };

    // Template functions
    template <class Type, class Allocator>
    bool operator==(const vector<Type, Allocator>& left,
                    const vector<Type, Allocator>& right)
    {
        if (left.size() != right.size()) { return false; }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] != right[i])
            {
                return false;
            }
        }
        return true;
    }
    template <class Type, class Allocator>
    bool operator!=(const vector<Type, Allocator>& left,
                    const vector<Type, Allocator>& right)
    {
        return !(left == right);
    }
    template <class Type, class Allocator>
    bool operator<(const vector<Type, Allocator>& left,
                   const vector<Type, Allocator>& right)
    {
        if (left.size() > right.size()) { return false; }
        else if (left.size() < right.size()) { return true; }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] != right[i])
            {
                if (left[i] < right[i])
                    return true;
            }
        }
        return false;
    }
    template <class Type, class Allocator>
    bool operator>(const vector<Type, Allocator>& left,
                   const vector<Type, Allocator>& right)
    {
        if (left.size() > right.size()) { return true; }
        else if (left.size() < right.size()) { return false; }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] != right[i])
            {
                if (left[i] > right[i])
                    return true;
            }
        }
        return false;
    }
    template <class Type, class Allocator>
    bool operator<=(const vector<Type, Allocator>& left,
                    const vector<Type, Allocator>& right)
    {
        if (left.size() > right.size()) { return false; }
        else if (left.size() < right.size()) { return true; }
        if (left == right) { return true; }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] != right[i])
            {
                if (left[i] < right[i])
                    return true;
            }
        }
        return false;
    }
    template <class Type, class Allocator>
    bool operator>=(const vector<Type, Allocator>& left,
                    const vector<Type, Allocator>& right)
    {
        if (left.size() > right.size()) { return true; }
        else if (left.size() < right.size()) { return false; }
        if (left == right) { return true; }
        for (int i = 0; i < left.size(); i++)
        {
            if (left[i] != right[i])
            {
                if (left[i] > right[i])
                    return true;
            }
        }
        return false;
    }

    template <class Type, class Allocator>
    void swap(vector<Type, Allocator>& left,
              vector<Type, Allocator>& right)
    {
        left.swap(right);
    }
}

#endif