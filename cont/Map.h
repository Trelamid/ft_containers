//
// Created by Prime_Games_2 on 30.06.2022.
//

#include "Tree.hpp"
#include "iterator_traits.h"
#include <ostream>
#include <iostream>

#ifndef FT_CONTAINERS_MAP_H
#define FT_CONTAINERS_MAP_H

namespace ft {
	template<class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<Node<Key, T> >  >
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const Key, T> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;    //Signed integer type (usually std::ptrdiff_t)
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef ft::Tree<Key, mapped_type, key_compare, allocator_type> ftTree;
		typedef typename ftTree::iterator iterator;
		typedef typename ftTree::reverse_iterator reverse_iterator;
		typedef map<key_type, mapped_type, key_compare, allocator_type> thisMap;
	protected:
		ftTree tree;
		allocator_type alloc;
		size_t _size;
	public:
		map() {
			_size = 0;
//			tree = ftTree();
//			alloc = allocator_type();
		};

		~map(){}

		thisMap &operator=(const thisMap &otherMap) {
			alloc = otherMap.alloc;
			tree = otherMap.tree;
			_size = otherMap._size;
			return this;
		}

		mapped_type &operator[](key_type key) {
			ft::Node<Key, mapped_type> auf = tree.find(key);
			return auf.value;
		}

		allocator_type &get_allocator() {
			return alloc;
		}

		mapped_type &at(const key_type &key) {
			try {
				ft::Node<Key, mapped_type> auf = tree.find(key);
				return auf.value;
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
		}

		iterator begin() {
			iterator it(tree.begin());
			return it;
		}

		iterator end() {
			return tree.end();
		}

		reverse_iterator rbegin() {
			return tree.rbegin();
		}

		reverse_iterator rend() {
			return tree.rend();
		}

		bool empty() {
			if (_size == 0)
				return true;
			else
				return false;
		}

		size_t size() { return _size; }

		size_t max_size() { return _size; }//auf
		void clear() {
			_size = 0;
			delete tree;
		}

		void insert(const value_type &pair) {
//			std::cout << pair.first << pair.second;
//			return;
			tree.insert(pair.first, pair.second);
			_size++;
		}

		void erase(const key_type &key) {
			tree.erase(key);
			_size--;
		}

		void swap() {
			//auf
		}

		size_t count(const key_type &key) {
			if (tree.find(key))
				return 1;
			else return 0;
		}

		iterator &find(const key_type &key) {
			iterator it(tree.find());
			return it; //auf
		}

		iterator lower_bound(const key_type &key) {
			iterator start(this->begin());
			iterator end(tree.end());
			while ((*start)->first < key && start != end)
				start++;
			return start;
		}

		iterator upper_bound(const key_type &key) {
			iterator start(this->begin());
			iterator end(tree.end());
			while ((*start)->first <= key && start != end)
				start++;
			return start;
		}

		key_compare key_comp() {
			key_compare ket;
			return ket;
		}

	};
}
#endif //FT_CONTAINERS_MAP_H
