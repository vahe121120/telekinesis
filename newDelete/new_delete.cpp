#include <iostream>
#include <cstdlib>

using namespace std;

// Dynamic memory managment for single object

void* mynew(size_t size)
{
	void* ptr = malloc(size);

	if ( !ptr )
		throw bad_alloc();

	return ptr;
}

void mydelete(void* ptr)
{
	if ( ptr )
		free(ptr);
}

template <typename T>
T* myNew(T value = 0)
{
	void* ptr = mynew(sizeof(T));
	T* p = static_cast<T*>(ptr);
	*p = value;

	return p;
}

template <typename T>
void myDelete(T* ptr)
{
	void* p = static_cast<void*>(ptr);
	mydelete(p);
}


// Dynamic memory managment for arrays

void* dynarr(size_t size, size_t type)			// size -> array length,  type -> type size
{
	if ( !size || !type )
		throw bad_alloc();

	void* p = malloc(size * type);

	if ( !p )
		throw bad_alloc();
	return p;
}

template <typename T>
T* dynArr(size_t size)
{
	void* ptr = dynarr(size, sizeof(T));
	T* p = static_cast<T*>(ptr);
		
	return p;
}


void dyn_arr_del(void* ptr)
{
	if ( ptr )
		free(ptr);
}


template <typename T>
void dynArrDel(T* ptr)
{
	void* p = static_cast<void*>(ptr);
	dyn_arr_del(p);
}
