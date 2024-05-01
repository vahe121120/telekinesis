#ifndef __VECTOR_HEADER__
#define __VECTOR_HEADER__

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
		using const_value_type = const value_type;
		using const_reference = const value_type&;
		using self_referenceL = vector<value_type>&;
		using self_referenceR = vector<value_type>&&;
		using const_self_reference = const vector<value_type>&;
		using pointer = T*;

	public:
		vector();				// default
		vector(size_type s);			// parametric
		vector(size_type s, const_value_type val); // parametric
		vector(std::initializer_list<T> l);	// dynamic initializing vector
        vector(self_referenceL rhv);	// copy
		vector(self_referenceR rhv); //move
		~vector();				// destructor
		
	public:
		const_self_reference operator=(const_self_reference rhv);
		const_self_reference operator=(self_referenceR rhv);
		reference operator[](size_type index);
		reference operator[](size_type index) const;
		reference at(const size_type index);
		void resize(const size_type s);
		void resize(const size_type s, const_value_type val);
		reference front();
	
	public:
		reference back();
		const_reference insert(const size_type index, const_value_type val);
		void remove(size_type index);
		void push_back(const_value_type val);
		void pop_back();
		pointer data();

	public:
		void recap();
		void clear();
		bool empty();
		size_type size();
		size_type capacity();
};



#include "vector_implement.h"

#endif
