#ifndef __FORWARD_LIST__
#define __FORWARD_LIST__

#include <initializer_list>

template <typename T>
class forward_list
{
	private:
		struct Node
		{
			T data;
			Node* next;
		};

	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using pointer = value_type*;
		using self_referenceL = forward_list<value_type>&;
		using self_referenceR = forward_list<value_type>&&;
		using const_self_reference = const self_referenceL;

	public:
		forward_list();
		forward_list(size_type size);
		forward_list(size_type size, value_type val);
		forward_list(std::initializer_list<value_type> l);
		forward_list(self_referenceL rhv);		// copy ctor
		forward_list(self_referenceR rhv);		// move ctor
		~forward_list();

	public:
		self_referenceL operator=(self_referenceL rhv);		// copy assignment
		self_referenceL operator=(self_referenceR rhv);		// move assignment
		reference operator[](size_type index);
		const_reference operator[](size_type index) const;
		reference at(const size_type index);
		void resize(const size_type size);
		void resize(const size_type size, const value_type value);
		reference front();

	public:
		reference back();
		void insert(const size_type index, const value_type value);
		void remove(size_type index);
		void push_back(const value_type value);
		void pop_back();
		pointer data();

	public:
		void recap(size_type cap);
		void clear();
		bool empty();
		size_type size();
		size_type capacity();

	private:
		Node* head;
};

#include "list_implementation.h"

#endif