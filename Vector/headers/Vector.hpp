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
		using reference = T&;
		using const_value_type = const T;
		using const_reference = const T&;
		using size_type = size_t;
		using self_reference = vector<T>&;
		using const_self_reference = const vector&;
		using self_referenceR = vector<value_type>&&;
		using const_self_referenceT = const vector<value_type>&;
		using const_self_referenceTT = const vector<value_type>&&;
		using pointer = T*;
		

	public:
		vector();				// default
		vector(size_type);			// parametric
		vector(size_type, const_value_type); // parametric
		vector(std::initializer_list<T>);	// dynamic initializing vector
        vector(const_self_referenceT);	// copy
		vector(const_self_referenceTT); //move
		~vector();				// destructor
		
	public:
		const_self_referenceT operator=(const_self_referenceT);
		const_self_referenceT operator=(self_referenceR);
		reference operator[](const size_type);
		reference at(const size_type);
		void resize(const size_type);
		void resize(const size_type, const_value_type);
		reference front();
	
	public:
		reference back();
		const_reference insert(const size_type, const_value_type);
		void remove(size_type);
		void push_back(const_value_type);
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
