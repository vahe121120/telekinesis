#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <initializer_list>

template <typename T>
class vector
{
	private:
		size_t len;
		size_t cap;
		T* arr;

	public:
		using value_type = T;
		using size_type = size_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using self_referenceL = vector<value_type>&;
		using self_referenceR = vector<value_type>&&;
		using const_self_reference = const vector<value_type>&;
		using pointer = value_type*;
		using const_pointer = const pointer;

	public:
		vector();				// default
		vector(size_type s);			// parametric
		vector(size_type s, value_type val); // parametric
		vector(std::initializer_list<T> l);	// dynamic initializing vector
        vector(self_referenceL rhv);	// copy
		vector(self_referenceR rhv); //move
		~vector();				// destructor
		
	public:
		class const_iterator;
		class iterator;
		class const_reverse_iterator;
		class reverse_iterator;

	public:
		const_self_reference operator=(const_self_reference rhv);
		const_self_reference operator=(self_referenceR rhv);
		reference operator[](size_type index);
		const_reference operator[](size_type index) const;
		reference at(size_type index);
		const_reference at(size_type index) const;
		void resize(size_type s);
		void resize(size_type s, value_type val);
		reference front();
	
	public:
		reference back();
		iterator insert(const_iterator pos, const_reference val);
		iterator insert(const_iterator pos, size_type count, const_reference val);
		iterator insert(const_iterator pos, std::initializer_list<value_type> init);


		void erase(size_type index);
		void push_back(value_type val);
		void pop_back();
		pointer data();

	public:
		void recap();
		void clear() noexcept;
		bool empty();
		size_type size();
		size_type capacity();

	public:
		const_iterator cbegin() const;
		const_iterator cend() const;

	public:
		iterator begin();
		iterator begin() const;
		iterator end();
		iterator end() const;

	public:
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

	public:
		reverse_iterator rbegin();
		reverse_iterator rbegin() const;
		reverse_iterator rend();
		reverse_iterator rend() const;
};

template <typename T>
class vector<T>::const_iterator
{
	protected:
		T* ptr;
		friend class vector;

	public:
		const_iterator();
		const_iterator(T* ptr);
		const_iterator(const const_iterator& rhv);
		const_iterator(const_iterator&& rhv);
	public:
		const_iterator& operator=(const const_iterator& rhv);
		const_iterator& operator=(const_iterator&& rhv);
		// const_reference operator[](size_t index);
		const_reference operator[](size_t index) const;
	public:
		// pre-fix
		const_iterator& operator++();
		// post-fix
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
		const_iterator operator+(int ind) const;
		const_iterator operator-(int ind) const;
		const_reference operator*();
		const_pointer operator->();
	public:
		bool operator==(const const_iterator& other) const;
		bool operator!=(const const_iterator& other) const;
		bool operator<(const const_iterator& other) const;
		bool operator<=(const const_iterator& other) const;
		bool operator>(const const_iterator& other) const;
		bool operator>=(const const_iterator& other) const;
};

template <typename T>
class vector<T>::iterator : public const_iterator
{
	private:
		T* ptr;

	public:
		iterator();
		iterator(T* ptr);
		iterator(iterator& rhv);
		iterator(iterator&& rhv);

	public:
		iterator& operator=(iterator& rhv);
		iterator& operator=(iterator&& rhv);
		reference operator[](size_t index);
		reference operator[](size_t index) const;

	public:
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		iterator operator+(int ind);
		iterator operator-(int ind);
		reference operator*();
		pointer operator->();

	public:
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		bool operator<(const iterator& other) const;
		bool operator<=(const iterator& other) const;
		bool operator>(const iterator& other) const;
		bool operator>=(const iterator& other) const;
};


template <typename T>
class vector<T>::const_reverse_iterator
{
	private:
		T* ptr;
		friend class vector;

	public:
		const_reverse_iterator();
		const_reverse_iterator(T* ptr);
		const_reverse_iterator(const const_reverse_iterator& rhv);
		const_reverse_iterator(const_reverse_iterator&& rhv);
	public:
		const_reverse_iterator& operator=(const const_reverse_iterator& rhv);
		const_reverse_iterator& operator=(const_reverse_iterator&& rhv);
		// const_reference operator[](size_t index);
		const_reference operator[](size_t index) const;
	public:
		// pre-fix
		const_reverse_iterator& operator++();
		// post-fix
		const_reverse_iterator operator++(int);
		const_reverse_iterator& operator--();
		const_reverse_iterator operator--(int);
		const_reverse_iterator operator+(int ind);
		const_reverse_iterator operator-(int ind);
		const_reference operator*();
		const_pointer operator->();
	public:
		bool operator==(const const_reverse_iterator& other) const;
		bool operator!=(const const_reverse_iterator& other) const;
		bool operator<(const const_reverse_iterator& other) const;
		bool operator<=(const const_reverse_iterator& other) const;
		bool operator>(const const_reverse_iterator& other) const;
		bool operator>=(const const_reverse_iterator& other) const;
};


template <typename T>
class vector<T>::reverse_iterator : public const_reverse_iterator
{
	private:
		T* ptr;
	
	public:
		reverse_iterator();
		reverse_iterator(T* ptr);
		reverse_iterator(const reverse_iterator& rhv);
		reverse_iterator(reverse_iterator&& rhv);
	public:
		reverse_iterator& operator=(const reverse_iterator& rhv);
		reverse_iterator& operator=(reverse_iterator&& rhv);
		reference operator[](size_t index);
		reference operator[](size_t index) const;
	public:
		// pre-fix
		reverse_iterator& operator++();
		// post-fix
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);
		reverse_iterator operator+(int ind);
		reverse_iterator operator-(int ind);
		reference operator*();
		pointer operator->();
	public:
		bool operator==(const reverse_iterator& other) const;
		bool operator!=(const reverse_iterator& other) const;
		bool operator<(const reverse_iterator& other) const;
		bool operator<=(const reverse_iterator& other) const;
		bool operator>(const reverse_iterator& other) const;
		bool operator>=(const reverse_iterator& other) const;

};


#include "vector_implement.h"

#endif	// __VECTOR_H__
