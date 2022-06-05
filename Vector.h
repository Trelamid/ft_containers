//
// Created by Prime_Games_2 on 02.06.2022.
//

#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#include <ostream>
#include <memory>
#include <algorithm>
#include <iostream>
#include <string>

namespace ft {
    template<typename T, class Alloc = std::allocator<T> >
    class vector {
	private:
		T* _arr;
		Alloc alloc;
		unsigned int _size;
		unsigned int _capacity;
    public:
		class iterator;

		iterator begin(){return iterator(_arr[0]);}
		iterator end(){return iterator(_arr[_size]);}

		const iterator begin() const{return iterator(_arr[0]);}
		const iterator end() const{return iterator(_arr[_size]);}

		class iterator
		{
			T* value;
		public:
			iterator(T* first){value = first;}

			T &operator*(){return *this->value;}
			T &operator+(int n){return *(value+n);}
			T &operator-(int n){return *(value-n);}

			T operator--(int){
				T prev = *value;
				--value;
				return prev;}
			T operator++(int){
				T prev = *value;
				++value;
				return prev;}
			T &operator--(){return *--value;}
			T &operator++(){return *++value;}

			bool operator!=(const iterator &it){if(it.value == value) return false;return true;}
			bool operator==(const iterator &it){if(it.value == value) return true;return false;}
		};

        vector() {
			_arr = alloc.allocate(1);
			_size = 1;
			_capacity = 1;
		}

		vector(vector &vec) {
			_arr = alloc.allocate(vec.capacity());
			for (int i = 0; i < vec.size(); i++) {
				alloc.construct(&_arr[i], vec[i]);
			}
			_size = vec.size();
			_capacity = vec.capacity();
		}

		vector(size_t n, const T& val = T())
		{
			_arr = alloc.allocate(n);
			for (int i = 0; i < n; i++) {
				alloc.construct(&_arr[i], val);
			}
			_size = n;
			_capacity = n;
		}

		vector(iterator start, iterator end)
		{
			iterator auf = start;
			int size_it = 0;
			while(auf != end)
				size_it++;
			T *arr = alloc.allocate(size_it);
			_size = size_it;
			_capacity = size_it;
			for (int i = 0; i < size_it; i++) {
				alloc.construct(&_arr[i], *start);
				start++;
			}
		}

		~vector() {
			for (int i = 0; i < _size; i++) {
				alloc.destroy(&(_arr[i]));
			}
			alloc.deallocate(_arr, _capacity);
		}

		bool empty() {
			if(_size == 0)
				return true;
			else
				return false;
		}

		unsigned int size() const {
			return _size;
		}

		unsigned int capacity() const{
			return _capacity;
		}

//		operator=	//Копирует значение одного вектора в другой.	O(n)
//		operator==	//Сравнение двух векторов	O(n)
		T &at(int index){if(index < _size)return _arr[index];else throw std::runtime_error("Error");}	//Доступ к элементу с проверкой выхода за границу	O(1)
		T &front(){return _arr[0];}	//Доступ к первому элементу	O(1)
		T &back(){return _arr[_size - 1];}	//Доступ к последнему элементу	O(1)
		iterator rbegin()	//Возвращает reverse_iterator на конец текущего вектора.	O(1)
		{

		}
		iterator rend()	//Возвращает reverse_iterator на начало вектора.	O(1)
		{

		}
		unsigned int max_size(){return _capacity;}//	Возвращает максимально возможное количество элементов в векторе	O(1)
		void reserve(unsigned int newCap)	//Устанавливает минимально возможное количество элементов в векторе	O(n)
		{
			if(newCap > capacity())
			{
				&_arr[capacity()] = alloc.allocate(newCap - capacity());
			}
		}
		void shrink_to_fit()	//Уменьшает количество используемой памяти за счёт освобождения неиспользованной (C++11)	O(1)
		{
			for (int i = size(); i < capacity(); i++) {
				alloc.deallocate(_arr[i]);
			}
			_capacity = _size;
		}
		void clear()	//Удаляет все элементы вектора	O(n)
		{
			for (int i = 0; i < _size; i++) {
				alloc.destroy(&_arr[i]);
			}
			_size = 0;
		}
		iterator insert(iterator pos, const T& value)	//Вставка элементов в вектор	Вставка в конец, при условии, что память не будет перераспределяться — O(1), в произвольное место — O(n)
		{
			T* _newArr;
			_newArr = alloc.allocate(capacity()+1);
			int i = 0;
			while(_arr[i] != *pos)
			{
				alloc.construct(&_newArr[i], _arr[i]);
				alloc.destroy(&_arr[i]);
				i++;
			}
			alloc.construct(&_newArr[i], value);
			i++;
			while(i <= size())
			{
				alloc.construct(&_newArr[i], _arr[i - 1]);
				alloc.destroy(&_arr[i - 1]);
				i++;
			}
			alloc.deallocate(_arr, capacity());
			_capacity += 1;
			++_size;
			_arr = _newArr;
		}
		iterator insert(iterator pos, unsigned int count, const T& value)
		{
			T* _newArr;
			_newArr = alloc.allocate(capacity()+count);
			int i = 0;
			while(_arr[i] != *pos)
			{
				alloc.construct(&_newArr[i], _arr[i]);
				alloc.destroy(&_arr[i]);
				i++;
			}
			int start = 0;
			while(start < count)
			{
				alloc.construct(&_newArr[i+start], value);
				start++;
			}
			while(i <= size())
			{
				alloc.construct(&_newArr[i + start], _arr[i]);
				alloc.destroy(&_arr[i]);
				i++;
			}
			alloc.deallocate(_arr, capacity());
			_capacity += count;
			_size += count;
			_arr = _newArr;
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last)
		{
			InputIt startIt = first;
			int count;
			while(startIt != last)
			{
				count++;
				startIt++;
			}
			T* _newArr;
			_newArr = alloc.allocate(capacity()+count);
			int i = 0;
			while(_arr[i] != *pos)
			{
				alloc.construct(&_newArr[i], _arr[i]);
				alloc.destroy(&_arr[i]);
				i++;
			}
			int start = 0;
			while(start < count)
			{
				alloc.construct(&_newArr[i+start], *first);
				first++;
				start++;
			}
			while(i <= size())
			{
				alloc.construct(&_newArr[i + start], _arr[i]);
				alloc.destroy(&_arr[i]);
				i++;
			}
			alloc.deallocate(_arr, capacity());
			_capacity += count;
			_size += count;
			_arr = _newArr;
		}
		void erase(iterator pos)
		{
			alloc.destroy(&*pos);
		}
		void erase(iterator first, iterator end)	//Удаляет указанные элементы вектора (один или несколько)	O(n)
		{
			while(first != end)
			{
				alloc.destroy(&*first);
				first++;
			}
		}
		void push_back(const T& value)	//Вставка элемента в конец вектора	O(1)
		{
			if(size()<capacity())
			{
				alloc.construct(&_arr[size()], value);
				++_size;
			}
			else
			{
				T* _newArr = alloc.allocate(capacity() * 2);
				for (int i = 0; i < _size; i++) {
					alloc.construct(&_newArr[i], _arr[i]);
					alloc.destroy(&_arr[i]);
				}
				alloc.construct(&_newArr[_size], value);
				alloc.deallocate(_arr, capacity());
				_capacity *= 2;
				++_size;
				_arr = _newArr;
			}
		}
		void pop_back()	//Удалить последний элемент вектора	O(1)
		{
			alloc.destroy(&_arr[size() - 1]);
			--_size;
		}
		void resize( unsigned int count, T value = T() )//Изменяет размер вектора на заданную величину	O(n)
		{
			if(size() > count)
			{
				unsigned int i = count;
				while(i < size())
				{
					alloc.destroy(&*_arr[i]);
					i++;
				}
			}
			if(count > size() && count <= capacity())
			{
				unsigned int i = size();
				while(i < count)
				{
					alloc.construct(&*_arr[i], value);
					i++;
				}
			}
			else if(count > size() && count > capacity())
			{
				T* _newArr = alloc.allocate(count);
				for (int i = 0; i < _size; i++) {
					alloc.construct(&_newArr[i], _arr[i]);
					alloc.destroy(&_arr[i]);
				}
				for (int i = _size; i < count; i++) {
					alloc.construct(&_newArr[i], value);
				}
				alloc.deallocate(_arr, capacity());
				_capacity = count;
				_size = count;
				_arr = _newArr;
			}
		}
		void swap(vector &vec2)	//Обменять содержимое двух векторов	O(1)
		{
			int c_size = size();
			int c_capacity = capacity();
			T *c_arr = this->_arr;

			this->_arr = vec2._arr;
			this->_size = vec2.size();
			this->_capacity = vec2.capacity();

			vec2._arr = c_arr;
			vec2._size = c_size;
			vec2._capacity = c_capacity;
		}
		void assign(const unsigned int count, const T& value)	//Ассоциирует с вектором поданные значения	O(n), если установлен нужный размер вектора, O(n*log(n)) при перераспределении памяти
		{
			for (int i = 0; i < _size; i++) {
				alloc.destroy(&(_arr[i]));
			}
			alloc.deallocate(_arr, _capacity);

			_arr = alloc.allocate(count);
			for (int i = 0; i < count; i++) {
				alloc.construct(&_arr[i], value);
			}
			_size = count;
			_capacity = count;
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{
			for (int i = 0; i < _size; i++) {
				alloc.destroy(&(_arr[i]));
			}
			alloc.deallocate(_arr, _capacity);

			int count = 0;
			InputIt help = first;
			while(help != last)
			{
				count++;
				help++;
			}

			_arr = alloc.allocate(count);
			for (int i = 0; i < count; i++) {
				alloc.construct(&_arr[i], *first);
				first++;
			}
		}

		std::allocator<T> &get_allocator(){return alloc;}

		T& operator[](unsigned int index) {
			return _arr[index];
		}

		const T& operator[](unsigned int index) const {
			return _arr[index];
		}

		friend std::ostream& operator<<(std::ostream &os, const ft::vector<T> vector)
		{
			for (int i = 0; i < vector.size(); i++) {
				os << vector[i];
			}
			return os;
		}
    };
}
template<typename _Iterator>
struct iterator_traits
{
	typedef typename _Iterator::iterator_category iterator_category;
	typedef typename _Iterator::value_type        value_type;
	typedef typename _Iterator::difference_type   difference_type;
	typedef typename _Iterator::pointer           pointer;
	typedef typename _Iterator::reference         reference;
};




#endif //FT_CONTAINERS_VECTOR_H
