/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtil.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:08:41 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/10/25 09:08:41 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPUTIL_HPP
#define MAPUTIL_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        pair() : first(first_type()), second(second_type()) {}
        template <class U, class V>
        pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
        pair(const first_type& a, const second_type& b) : first(a), second(b) {}

        first_type first;
        second_type second;
    };
    
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return pair<T1, T2>(x, y);
    }

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
    template <class T1, class T2>
    bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
    {
        return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
    }
    template <class T1, class T2>
    bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
    {
        return (!(lhs == rhs));
    }
    template <class T1, class T2>
    bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
    {
        return (!(rhs < lhs));
    }
    template <class T1, class T2>
    bool operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
    {
        return (rhs < lhs);
    }
    template <class T1, class T2>
    bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
    {
        return (!(lhs < rhs));
    }

    template <class Type>
    void swap(Type &a, Type &b)
    {
        Type temp = a;
        a = b;
        b = temp;
    }

    template <bool B, class T = void, class U = void>
    struct conditional {};

    template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };

    template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <class T, class U>
    struct is_same
    {
        static const bool value = false;
    };

    template <class T>
    struct is_same<T, T>
    {
        static const bool value = true;
    };
}

#endif