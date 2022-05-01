/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:13 by hyungyyo          #+#    #+#             */
/*   Updated: 2021/10/07 22:13:12 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include "mapUtil.hpp"

namespace ft
{
    template <class Key, class Type, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, Type> > >
    class map
    {
    public:
        /*
        * Struct
        */
        struct s_node
        {
            ft::pair<const Key, Type> data;
            bool color;
            s_node* left;
            s_node* right;
            s_node* parent;

            s_node(ft::pair<const Key, Type> data) : data(data) {}
            const Key& key()
            {
                return data.first;
            }
            Type& val()
            {
                return data.second;
            }
        };

    public:
        /*
        * typedef
        */
        typedef Key                                                 key_type;
        typedef Type                                                mapped_type;
        typedef ft::pair<const key_type, mapped_type>               value_type;
        typedef Compare                                             key_compare;
    
    public:
        /*
        * Iterator class
        */
        template <bool IsConst>
        class mapIterator
        {
        public:
            typedef ft::pair<const Key, Type>                                           pair_type;
            typedef typename ft::conditional<IsConst, const pair_type, pair_type>::type value_type;
            typedef typename ft::conditional<IsConst, const s_node, s_node>::type       node_type;
            typedef std::ptrdiff_t                                                      difference_type;
            typedef std::size_t                                                         size_type;

        public:
            mapIterator() { ptr = NULL; }
            mapIterator(node_type* ptr)
            {
                this->ptr = ptr;
            }
            template <bool B>
            mapIterator(mapIterator<B>& cMapIter, typename ft::enable_if<!B>::type* = 0)
            {
                this->ptr = cMapIter.ptr;
            }
            ~mapIterator() {}

            mapIterator& operator=(const mapIterator& mapIter)
            {
                this->ptr = mapIter.getPtr();
                return *this;
            }
            template <bool B>
            bool operator==(const mapIterator<B>& mapIter) const
            {
                return this->ptr == mapIter.getPtr();
            }
            template <bool B>
            bool operator!=(const mapIterator<B>& mapIter) const
            {
                return this->ptr != mapIter.getPtr();
            }

            mapIterator& operator++()
            {
                this->nextNode();
                return *this;
            }
            mapIterator& operator--()
            {
                this->prevNode();
                return *this;
            }
            mapIterator operator++(int)
            {
                mapIterator<IsConst> x(*this);
                this->nextNode();
                return x;
            }
            mapIterator operator--(int)
            {
                mapIterator<IsConst> x(*this);
                this->prevNode();
                return x;
            }
            value_type& operator*() const
            {
                return ptr->data;
            }
            value_type* operator->() const
            {
                return &ptr->data;
            }
            node_type* getPtr() const
            {
                return ptr;
            }

        private:
            void nextNode()
            {
                if (ptr->right != ptr->right->left)
                {
                    ptr = ptr->right;
                    while (ptr->left != ptr->left->left)
                    {
                        ptr = ptr->left;
                    }
                }
                else
                {
                    while (ptr == ptr->parent->right && ptr != ptr->parent)
                    {
                        ptr = ptr->parent;
                    }
                    ptr = ptr->parent;
                }
            }
            void prevNode()
            {
                 if (ptr == ptr->parent)
                {
                    while (ptr->right != ptr->right->left)
                    {
                        ptr = ptr->right;
                    }
                }
                else if (ptr->left != ptr->right->left)
                {
                    ptr = ptr->left;
                    while (ptr->right != ptr->right->left)
                    {
                        ptr = ptr->right;
                    }
                }
                else
                {
                    while (ptr == ptr->parent->left && ptr != ptr->parent)
                    {
                        ptr = ptr->parent;
                    }
                    ptr = ptr->parent;
                }
            }

        private:
            node_type* ptr;
        };

        template <class it>
        class mapReverseIterator
        {
        public:
            mapReverseIterator()
            {
                this->iter = it();
            }
            mapReverseIterator(typename it::value_type* ptr)
            {
                this->iter = it(ptr);
            }
            mapReverseIterator(const it& x)
            {
                this->iter = x;
                --iter;
            }
            template <class U>
            friend class mapReverseIterator;
            template <class U>
            mapReverseIterator(const mapReverseIterator<U>& copy)
            {
                this->iter = copy.getIt();
            }
            ~mapReverseIterator() {}

            mapReverseIterator& operator=(const mapReverseIterator& operand)
            {
                this->iter = operand.getIt();
                return *this;
            }
            mapReverseIterator& operator+=(int n)
            {
                this->iter -= n;
                return *this;
            }
            mapReverseIterator& operator-=(int n)
            {
                this->iter += n;
                return *this;
            }

            template <class U>
            mapReverseIterator& operator==(const mapReverseIterator<U>& operand) const
            {
                return iter == operand.getIt();
            }
            template <class U>
            bool operator!=(const mapReverseIterator<U>& operand) const
            {
                return iter != operand.getIt();
            }
            template <class U>
            bool operator<(const mapReverseIterator<U>& operand) const
            {
                return iter > operand.getIt();
            }
            template <class U>
            bool operator<=(const mapReverseIterator<U>& operand) const
            {
                return iter >= operand.getIt();
            }
            template <class U>
            bool operator>(const mapReverseIterator<U>& operand) const
            {
                return iter < operand.getIt();
            }
            template <class U>
            bool operator>=(const mapReverseIterator<U>& operand) const
            {
                return iter <= operand.getIt();
            }
            mapReverseIterator& operator++()
            {
                --iter;
                return *this;
            }
            mapReverseIterator& operator--()
            {
                ++iter;
                return *this;
            }
            mapReverseIterator operator++(int)
            {
                mapReverseIterator<it> x(*this);
                --iter;
                return x;
            }
            mapReverseIterator operator--(int)
            {
                mapReverseIterator<it> x(*this);
                ++iter;
                return x;
            }
            typename it::value_type& operator*() const
            {
                return *iter;
            }
            typename it::value_type* operator->() const
            {
                return &(*iter);
            }

            it base()
            {
                return ++it(iter);
            }
            it getIt() const
            {
                return iter;
            }
        
        private:
            it iter;
        };

        /*
        * valueCompare class
        */
        class valueCompare
        {
        public:
            friend class map;

            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            bool operator()(const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        protected:
            valueCompare(Compare c)
            {
                comp = c;
            }

        protected:
            Compare comp;
        };

    public:
        typedef valueCompare                                        value_compare;
        typedef typename Allocator::template rebind<s_node>::other  allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef mapIterator<false>                                  iterator;
        typedef mapIterator<true>                                   const_iterator;
        typedef mapReverseIterator<iterator>                        reverse_iterator;
        typedef mapReverseIterator<const_iterator>                  const_reverse_iterator;
        typedef typename mapIterator<false>::difference_type        difference_type;
        typedef typename mapIterator<false>::size_type              size_type;

    public:
        map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        {
            this->alloc = alloc;
            this->comp = comp;
            this->_new_nil_node();
        }
        map(const map& copy)
        {
            this->alloc = copy.alloc;
            this->comp = copy.comp;
            this->_new_nil_node();
            *this = copy;
        }
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
        {
            this->alloc = alloc;
            this->comp = comp;
            this->_new_nil_node();

            while (first != last)
                this->insert(*first++);
        }
        ~map()
        {
            this->clear();
            alloc.destroy(dataPool);
            alloc.deallocate(dataPool, 1);
        }

        map& operator=(const map& operand)
        {
            if (this == *operand)
            {
                return *this;
            }

            this->clear();
            alloc = operand.alloc;
            comp = operand.comp;

            for (const_iterator it = operand.begine(); it != operand.end(); it++)
            {
                this->insert(*it);
            }
            return *this;
        }

        iterator begin()
        {
            return iterator(this->_leftmost(dataPool->right));
        }
        const_iterator begin() const
        {
            return const_iterator(this->_leftmost(dataPool->right));
        }
        iterator end()
        {
            return iterator(dataPool);
        }
        const_iterator end() const
        {
            return const_iterator(dataPool);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(dataPool);
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(dataPool);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(this->_leftmost(dataPool->right));
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(this->_leftmost(dataPool->right));
        }

        bool empty() const
        {
            return dataPool == dataPool->right;
        }

        size_type size() const
        {
            size_type ret = 0;
            for (const_iterator it = this->begin(); it != this->end(); it++)
            {
                ret++;
            }
            return ret;
        }
        size_type max_size() const
        {
            return alloc.max_size();
        }
        
        ft::pair<iterator, bool> insert(const value_type& value)
        {
            iterator it;
            if (this->count(value.first))
            {
                it = this->find(value.first);
                return ft::make_pair(it, false);
            }
            else
            {
                it = iterator(this->_new_node(value));
                return ft::make_pair(it, true);
            }
        }
        iterator insert(iterator position, const value_type& value)
        {
            (void)position;
            return this->insert(value).first;
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
        {
            while (first != last)
            {
                this->insert(*first);
                first++;
            }
        }

        void erase(iterator position)
        {
            s_node* ptr = position.getPtr();

            if (ptr->left != dataPool && ptr->right != dataPool)
            {
                position--;
                this->_swap_nodes(ptr, position.getPtr());
                this->erase(ptr);
            }
            else
            {
                s_node* child = (ptr->left != dataPool) ? ptr->left : ptr->right;

                if (child != dataPool)
                {
                    child->parent = ptr->parent;
                }
                if (ptr->parent->left == ptr)
                {
                    ptr->parent->left = child;
                }
                else
                {
                    ptr->parent->right = child;
                }
                this->_remove_node(ptr, child);
            }
        }
        size_type erase(const key_type& key)
        {
            if (this->count(key))
            {
                this->erase(this->find(key));
                return 1;
            }
            return 0;
        }
        void erase(iterator first, iterator last)
        {
            for (iterator it = first++; it != last; it = first++)
            {
                this->erase(it);
            }
        }

        void swap(map& right)
        {
            ft::swap(alloc, right.alloc);
            ft::swap(comp, right.comp);
            ft::swap(dataPool, right.dataPool);
        }

        void clear()
        {
            iterator first = this->begin();
            for (iterator it = first++; it != this->end(); it = first++)
            {
                this->erase(it);
            }
        }

        key_compare key_comp() const
        {
            return key_compare();
        }
        value_compare value_comp() const
        {
            return value_compare(comp);
        }

        iterator find(const key_type& key)
        {
            if (this->count(key))
            {
                return iterator(this->_find_node(dataPool->right, key));
            }
            else
            {
                return this->end();
            }
        }
        const_iterator find(const key_type& key) const
        {
            if (this->count(key))
            {
                return const_iterator(this->_find_node(dataPool->right, key));
            }
            else
            {
                return this->end();
            }
        }

        size_type count(const key_type& key) const
        {
            size_type n = 0;

            for (const_iterator it = this->begin(); it != this->end(); it++)
            {
                if (this->_equal(key, it->first))
                {
                    n++;
                }
            }
            return n;
        }

        iterator lower_bound(const key_type& key)
        {
            iterator it = this->begin();
            while (this->comp(it->first, key) && it != this->end())
            {
                it++;
            }
            return it;
        }
        const_iterator lower_bound(const key_type& key) const
        {
            const_iterator it = this->begin();
            while (this->comp(it->first, key) && it != this->end())
            {
                it++;
            }
            return it;
        }
        
        iterator upper_bound(const key_type& key)
        {
            iterator it = this->begin();
            while (this->comp(key, it->first) == false && it != this->end())
            {
                it++;
            }
            return it;
        }
        const_iterator upper_bound(const key_type& key) const
        {
            const_iterator it = this->begin();
            while (this->comp(key, it->first) == false && it != this->end())
            {
                it++;
            }
            return it;
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key)
        {
            return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
        }
        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        {
            return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
        }

        allocator_type get_allocator() const
        {
            return allocator_type();
        }

        mapped_type& operator[](const key_type& key)
        {
            this->insert(ft::make_pair(key, mapped_type()));
            return this->find(key)->second;
        }

    private:
        void _new_nil_node()
        {
            dataPool = alloc.allocate(1);
            this->_construct(dataPool);
            dataPool->color = false;
        }

        s_node* _new_node(const value_type& value = value_type())
        {
            s_node* new_node = alloc.allocate(1);
            this->_construct(new_node, value);

            s_node* parent = this->_find_parent(dataPool->right, value.first);
            if (parent == dataPool || !this->comp(value.first, parent->key()))
            {
                parent->right = new_node;
            }
            else
            {
                parent->left = new_node;
            }
            new_node->parent = parent;
            this->_insertRB(new_node);

            return new_node;
        }
        void _construct(s_node* ptr, const value_type& value = value_type())
        {
            s_node temp(value);
            temp.left = dataPool;
            temp.right = dataPool;
            temp.parent = dataPool;
            temp.color = true;
            alloc.construct(ptr, temp);
        }

        void _swap_nodes(s_node* a, s_node* b)
        {
            if (a->left != b && a->left != dataPool)
			    a->left->parent = b;
            if (a->right != b && a->right != dataPool)
                a->right->parent = b;
            if (a->parent != b && a->parent != dataPool)
            {
                if (a->parent->left == a)
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }

            if (b->left != a && b->left != dataPool)
                b->left->parent = a;
            if (b->right != a && b->right != dataPool)
                b->right->parent = a;
            if (b->parent != a && b->parent != dataPool)
            {
                if (b->parent->left == b)
                    b->parent->left = a;
                else
                    b->parent->right = a;
            }

            if (a->parent == b)
                a->parent = a;
            if (a->left == b)
                a->left = a;
            if (a->right == b)
                a->right = a;
            if (b->parent == a)
                b->parent = b;
            if (b->left == a)
                b->left = b;
            if (b->right == a)
                b->right = b;

            ft::swap(a->parent, b->parent);
            ft::swap(a->left, b->left);
            ft::swap(a->right, b->right);
            ft::swap(a->color, b->color);

            if (dataPool->right == a)
                dataPool->right = b;
            else if (dataPool->right == b)
                dataPool->right = a;
        }
        void _remove_node(s_node* ptr, s_node* child)
        {
            this->_deleteRB(ptr, child);
            alloc.destroy(ptr);
            alloc.deallocate(ptr, 1);
        }

        s_node* _find_node(s_node* current, const key_type& key) const
        {
            if (current == dataPool || this->_equal(current->key(), key))
            {
                return current;
            }
            else if (this->comp(key, current->key()))
            {
                return this->_find_node(current->left, key);
            }
            else
            {
                return this->_find_node(current->right, key);
            }
        }
        s_node* _find_parent(s_node* current, const key_type& key) const
        {
            if (!this->comp(key, current->key()))
            {
                if (current->right == dataPool)
                {
                    return current;
                }
                else
                {
                    return this->_find_parent(current->right, key);
                }
            }
            else
            {
                if (current->left == dataPool)
                {
                    return current;
                }
                else
                {
                    return this->_find_parent(current->left, key);
                }
            }
        }

        s_node* _leftmost(s_node* root) const
        {
            while (root->left != root->left->left)
            {
                root = root->left;
            }
            return root;
        }

        bool _equal(const key_type& left, const key_type& right) const
        {
            return this->comp(left, right) == false && this->comp(right, left) == false;
        }

        void _insertRB(s_node* node)
        {
            s_node* parent = node->parent;
            s_node* grandparent = parent->parent;
            s_node* uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;

            if (parent == dataPool)
                node->color = false;
            else if (parent->color == false)
                return ;
            else if (uncle->color == true)
            {
                parent->color = false;
                uncle->color = false;
                grandparent->color = true;
                this->_insertRB(grandparent);
            }
            else if (uncle->color == false)
            {
                if (grandparent->left->left == node || grandparent->right->right == node)
                {
                    if (grandparent->left->left == node)
                        this->_LL(grandparent, parent);
                    else if (grandparent->right->right == node)
                        this->_RR(grandparent, parent);
                    ft::swap(grandparent->color, parent->color);
                }
                else
                {
                    if (grandparent->left->right == node)
                        this->_LR(grandparent, parent, node);
                    else if (grandparent->right->left == node)
                        this->_RL(grandparent, parent, node);
                    ft::swap(grandparent->color, node->color);
                }
		    }
        }
        void _deleteRB(s_node* v, s_node* u)
        {
            if (v->color == true || u->color == true)
            {
                u->color = false;
            }
            else
            {
                this->_doubleBlack(u, v->parent);
            }
        }

        void _doubleBlack(s_node* u, s_node* parent)
        {
            s_node * sibling = (parent->left != u) ? parent->left : parent->right;

            if (u == dataPool->right)
                return ;
            else if (sibling->color == false && (sibling->left->color == true || sibling->right->color == true))
            {
                if (sibling == parent->left && sibling->left->color == true)
                    this->_LL(parent, sibling);
                else if (sibling == parent->left && sibling->right->color == true)
                    this->_LR(parent, sibling, sibling->right);
                else if (sibling == parent->right && sibling->right->color == true)
                    this->_RR(parent, sibling);
                else if (sibling == parent->right && sibling->left->color == true)
                    this->_RL(parent, sibling, sibling->left);

                if (sibling->left->color == true)
                    sibling->left->color = false;
                else
                    sibling->right->color = false;
            }
            else if (sibling->color == false)
            {
                sibling->color = true;
                if (parent->color == true)
                    parent->color = false;
                else
                    this->_doubleBlack(parent, parent->parent);
            }
            else if (sibling->color == true)
            {
                if (sibling == parent->left)
                    this->_LL(parent, sibling);
                else
                    this->_RR(parent, sibling);
                ft::swap(parent->color, sibling->color);
                this->_doubleBlack(u, parent);
            }
        }

        void _LL(s_node* grandparent, s_node* parent)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = parent;
            }
            else
            {
                grandparent->parent->left = parent;
            }
            if (parent->right != dataPool)
            {
                parent->right->parent = grandparent;
            }
            grandparent->left = parent->right;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->right = grandparent;
        }
        void _RR(s_node* grandparent, s_node* parent)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = parent;
            }
            else
            {
                grandparent->parent->left = parent;
            }
            if (parent->left != dataPool)
            {
                parent->left->parent = grandparent;
            }
            grandparent->right = parent->left;
            parent->parent = grandparent->parent;
            grandparent->parent = parent;
            parent->left = grandparent;
        }
        void _LR(s_node* grandparent, s_node* parent, s_node* x)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = x;
            }
            else
            {
                grandparent->parent->left = x;
            }
            if (x->left != dataPool)
            {
                x->left->parent = parent;}
            if (x->right != dataPool)
            {
                x->right->parent = grandparent;
            }
            grandparent->left = x->right;
            parent->right = x->left;
            x->parent = grandparent->parent;
            grandparent->parent = x;
            parent->parent = x;
            x->left = parent;
            x->right = grandparent;
        }
        void _RL(s_node* grandparent, s_node* parent, s_node* x)
        {
            if (grandparent->parent->right == grandparent)
            {
                grandparent->parent->right = x;
            }
            else
            {
                grandparent->parent->left = x;
            }
            if (x->left != dataPool)
            {
                x->left->parent = grandparent;
            }
            if (x->right != dataPool)
            {
                x->right->parent = parent;
            }
            grandparent->right = x->left;
            parent->left = x->right;
            x->parent = grandparent->parent;
            grandparent->parent = x;
            parent->parent = x;
            x->left = grandparent;
            x->right = parent;
        }

    private:
        allocator_type  alloc;
        key_compare     comp;
        s_node*         dataPool;
    };

    template<class Key, class Type, class Compare, class Alloc>
    bool operator==(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
		return (equal(left.begin(), left.end(), right.begin(), right.end()));
	}
    template<class Key, class Type, class Compare, class Alloc>
    bool operator!=(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
        return (!(left == right));
    }
    template<class Key, class Type, class Compare, class Alloc>
    bool operator<(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
        return lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
    }
    template<class Key, class Type, class Compare, class Alloc>
    bool operator<=(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
        return (!(right < left));
    }
    template<class Key, class Type, class Compare, class Alloc>
    bool operator>(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
        return (right < left);
    }
    template<class Key, class Type, class Compare, class Alloc>
    bool operator>=(const map<Key, Type, Compare, Alloc>& left, const map<Key, Type, Compare, Alloc>& right)
    {
        return (!(left < right));
    }

    template<class Key, class Type, class Compare, class Alloc>
    void swap(map<Key, Type, Compare, Alloc>& left, map<Key, Type, Compare, Alloc>& right)
    {
        left.swap(right);
    }

    template <class T>
    bool equal(T& a, T& b)
    {
        return a == b;
    }
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}
		return (rit == rend);
	}
	template <class T>
	bool lexicographical_compare (T & a, T & b)
	{
		return (a < b);
	}
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return (false);
			else if (*lit < *rit)
				return (true);
			++lit, ++rit;
		}
		return (rit != rend);
	}
}

#endif