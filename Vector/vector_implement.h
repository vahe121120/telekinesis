#ifndef __VECTOR_IMPLEMENTATION__
#define __VECTOR_IMPLEMENTATION__

#include "Vector.hpp"
#include <initializer_list>



// Default constructor

template <typename T>
vector<T>::vector()
	: vector<value_type>::vector(0, value_type{})
{}


// Assignment constructor

template <typename T>
vector<T>::vector(size_type s)
	: vector<T>::vector(s, value_type{})
{}


// Parametric constructor

template <typename T>
vector<T>::vector(size_type s, value_type val)
	: len{s}
	, cap{s}
	, arr{nullptr}
{
	if ( s )
	{
		arr = new value_type [cap];
		for (int i = 0; i < s; ++i)
		{
			arr[i] = val;
		}
	}
}


// dynamic initializing vector <=> constructor

template <typename T>
vector<T>::vector(std::initializer_list<value_type> l)

	: len{ l.size() }
	, arr{ new value_type [this->len] }
{
	int i{};
	for ( auto value : l )
	{
		arr[i] = value;
		i++;
	}
}


// Copy constructor

template <typename T>
vector<T>::vector(self_referenceL rhv)
	: len{ rhv.size() }
	, cap{ rhv.capacity() }
	, arr{ new value_type [cap] }
{
	for (int i = 0; i < this->len; ++i)
	{
		this->arr[i] = rhv[i];
	}
}


// Move constructor

template <typename T>
vector<T>::vector(self_referenceR rhv)	
	: len{rhv.len}
	, cap{rhv.cap}
	, arr{rhv.arr}
{		
	rhv.arr = nullptr;
}


// Destructor

template <typename T>
vector<T>::~vector()
{
	this->clear();
}


// Copy assignment ( Deep copy )

template <typename T>
const vector<T>& vector<T>::operator=(const_self_reference rhv)
{
    if ( this != &rhv )
    {
		if ( arr )
        {
			this->clear();
        }
        arr = new value_type [this->cap];

        this->len = rhv.len;
        this->cap = rhv.cap;

        for (int i = 0; i < this->len; ++i)
        {
            this->arr[i] = rhv.arr[i];
        }
	} 

    return *this;
}


// Move assignment

template <typename T>
const vector<T>& vector<T>::operator=(self_referenceR rhv)
{
	if ( this != &rhv )
	{
		this->len = rhv.len;
		this->cap = rhv.cap;
		this->arr = rhv.arr;

		rhv.arr;
	}

	return *this;
}


// Subscript operator

template <typename T>
T& vector<T>::operator[](size_type index)
{
	return const_cast<reference>(static_cast<const_self_reference>(*this)[index]);
}


// Const subscript operator

template <typename T>
const T& vector<T>::operator[](size_type index) const
{
	return arr[index];
}


// at method

template <typename T>
T& vector<T>::at(size_type index)
{
	if ( index >= this->len ) throw;
	return arr[index];
}

template <typename T>
const T& vector<T>::at(size_type index) const
{
	if ( index >= this->len ) throw;
	return arr[index];
}


// resize method

template <typename T>
void vector<T>::resize(size_type s)
{
	resize(s, value_type{});
}


// resize method

template <typename T>
void vector<T>::resize(size_type s, value_type val)
{
	if ( s == this->len ) return;

	if ( s > this->len )
	{
		if ( s <= this->cap )
		{
			for ( int i = this->len; i < s; ++i )
			{
				arr[i] = val;
			}

			this->len = s;
		}
		else
		{
			vector<T>::recap();
			value_type* ptr = new value_type [this->cap];

			for (int i = 0; i < this->len; ++i)
			{
				ptr[i] = this->arr[i];
			}

			this->arr = ptr;
			delete [] ptr;
			this->len = s;
		}
	}
	else
	{
		this->len = s;
	}
}


// front method

template <typename T>
T& vector<T>::front()
{
	if ( this->len )
		return arr[0];
	throw;
}


// back method

template <typename T>
T& vector<T>::back()
{
	if ( this->len )
		return arr[len - 1];
	throw;
}


// insert method

// template <typename T>
// const T& vector<T>::insert(size_type index, value_type val)
// {
// 	if ( index >= this->len )
// 		throw;

// 	this->len++;

// 	if ( this->len >= this->cap )
// 		vector<value_type>::recap();

// 	pointer ptr = new value_type [this->len];


// 	for (int i = 0, j = 0; i < this->len; ++i, ++j)
// 	{
// 		if ( i == index )
// 		{
// 			ptr[i] = val;
// 			--j;
// 			continue;
// 		}

// 		ptr[i] = arr[j];
// 	}

// 	delete [] arr;
// 	arr = ptr;
// 	delete [] ptr;
// }

template <typename T>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, const_reference val)
{
	// calculating offset
	size_t index = pos.ptr - arr;

	++len;
	++cap;
	
	for ( int i = len; i >= index; --i )
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = val;

	return begin() + index;
}

template <typename T>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, size_type count, const_reference val)
{
	size_t index = pos.ptr - arr;

	len += count;
	cap += count;

	for ( int i = len + count - 1; i >= index + count - 1; --i )
	{
		arr[i] = arr[i - count];
	}

	for ( int i = index; i < index + count; ++i )
	{
		arr[i] = val;
	}
	
	return begin() + index;
}

template <typename T>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, std::initializer_list<value_type> init)
{
	size_t index = pos.ptr - arr;
	int count = init.size();

	for ( int i = len; i >= index; --i )
	{
		arr[i + count - 1] = arr[i - 1];
	}

	auto it = init.begin();

	for ( int i = index; i < len + index; ++i )
	{
		arr[i] = *it++;
	}

	len += count;
	cap += count;
	
	return begin() + index;
}


// erase method

template <typename T>
void vector<T>::erase(size_type index)
{
	if ( index >= this->len ) throw;

	value_type* ptr = new value_type [this->len - 1];

	for (int i = 0, j = 0; i < this->len; ++i, ++j)
	{	
		if ( j == index )
		{
			--i;
			continue;
		}
		ptr[i] = arr[j];
	}

	this->len--;

	delete [] arr;
	arr = ptr;
	delete [] ptr;
}


// push_back method

template <typename T>
void vector<T>::push_back(value_type val)
{
	if ( !arr )
	{
		this->cap = 5;
		this->len = 1;
		arr = new value_type [cap];
		arr[0] = val;
	}
	else
	{
		this->len++;
		if ( this->len >= this->cap )
			vector<value_type>::recap();
		this->arr[len - 1] = val;
	}
}


// pop_back method

template <typename T>
void vector<T>::pop_back()
{
	if ( !this->empty() )
	{
		this->len--;
	}
}


// data method

template <typename T>
T* vector<T>::data()
{
	return (arr + 0);
}


// recap method

template <typename T>
void vector<T>::recap()
{
	while ( this->cap < this->len )
	{
		this->cap *= 2;
	}
}


// clear method

template <typename T>
void vector<T>::clear() noexcept
{
	if ( arr )
	{
		for (int i = this->len; i >= 0; --i)
		{
			this->arr[i] = 0;
		}

		delete [] arr;
		arr = nullptr;

		this->len = 0;
		this->cap = 0;
	}
}


// empty method

template <typename T>
bool vector<T>::empty()
{
	return !this->len;
}


// size method

template <typename T>
size_t vector<T>::size()
{
	return this->len;
}


// capacity method

template <typename T>
size_t vector<T>::capacity()
{
	return this->cap;
}


template <typename T>
typename vector<T>::const_iterator
vector<T>::cbegin() const
{
	return vector<T>::const_iterator(arr);
}

template <typename T>
typename vector<T>::const_iterator
vector<T>::cend() const
{
	return vector<T>::const_iterator(arr + len);
}

template <typename T>
typename vector<T>::iterator
vector<T>::begin()
{
	return vector<T>::iterator(arr);
}

template <typename T>
typename vector<T>::iterator
vector<T>::begin() const
{
	return vector<T>::iterator(arr);
}

template <typename T>
typename vector<T>::iterator
vector<T>::end()
{
	return vector<T>::iterator(arr + len);
}

template <typename T>
typename vector<T>::iterator
vector<T>::end() const
{
	return vector<T>::iterator(arr + len);
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::crbegin() const
{
	return vector<T>::const_reverse_iterator(arr + len - 1);
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::crend() const
{
	return vector<T>::const_reverse_iterator(arr - 1);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rbegin()
{
	return vector<T>::reverse_iterator(arr + len - 1);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rbegin() const
{
	return vector<T>::reverse_iterator(arr + len - 1);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rend()
{
	return vector<T>::reverse_iterator(arr - 1);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rend() const
{
	return vector<T>::reverse_iterator(arr - 1);
}



// --------------------------------------------------

// Const Iterator class

template <typename T>
vector<T>::const_iterator::const_iterator() = default;

template <typename T>
vector<T>::const_iterator::const_iterator(T* ptr)
	: ptr{ptr}
{}

template <typename T>
vector<T>::const_iterator::const_iterator(const const_iterator& rhv)
	: ptr{rhv.ptr}
{}

template <typename T>
vector<T>::const_iterator::const_iterator(const_iterator&& rhv)
	: ptr{std::move(rhv.ptr)}
{
	rhv.ptr = nullptr;
}

template <typename T>
typename vector<T>::const_iterator&
vector<T>::const_iterator::operator=(const const_iterator& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
	}
	return *this;
}

template <typename T>
typename vector<T>::const_iterator&
vector<T>::const_iterator::operator=(const_iterator&& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
	return *this;
}

// template <typename T>
// typename vector<T>::const_reference
// vector<T>::const_iterator::operator[](size_t index)
// {
// 	return *(ptr + index);
// }

template <typename T>
typename vector<T>::const_reference
vector<T>::const_iterator::operator[](size_t index) const
{
	return *(ptr + index);
}

// pre-fix
template <typename T>
typename vector<T>::const_iterator&
vector<T>::const_iterator::operator++()
{
	*ptr++;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::const_iterator
vector<T>::const_iterator::operator++(int)
{
	pointer tmp = ptr;
	*ptr++;
	return vector<T>::const_pointer(tmp);
}

// pre-fix
template <typename T>
typename vector<T>::const_iterator&
vector<T>::const_iterator::operator--()
{
	*ptr--;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::const_iterator
vector<T>::const_iterator::operator--(int)
{
	pointer tmp = ptr;
	*ptr--;
	return vector<T>::const_pointer(tmp);
}

template <typename T>
typename vector<T>::const_iterator
vector<T>::const_iterator::operator+(int ind) const
{
	return const_iterator(ptr + ind);
}

template <typename T>
typename vector<T>::const_iterator
vector<T>::const_iterator::operator-(int ind) const
{
	return const_iterator(ptr - ind);
}

template <typename T>
typename vector<T>::const_reference
vector<T>::const_iterator::operator*()
{
	return *ptr;
}

template <typename T>
typename vector<T>::const_pointer
vector<T>::const_iterator::operator->()
{
	return ptr;
}

template <typename T>
bool
vector<T>::const_iterator::operator==(const const_iterator& other) const
{
	return (ptr == other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_iterator::operator!=(const const_iterator& other) const
{
	return (ptr == other.ptr ? false : true);
}

template <typename T>
bool
vector<T>::const_iterator::operator<(const const_iterator& other) const
{
	return (ptr < other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_iterator::operator<=(const const_iterator& other) const
{
	return (ptr <= other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_iterator::operator>(const const_iterator& other) const
{
	return (ptr > other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_iterator::operator>=(const const_iterator& other) const
{
	return (ptr >= other.ptr ? true : false);
}


// --------------------------------------------------

// Iterator class

template <typename T>
vector<T>::iterator::iterator() = default;

template <typename T>
vector<T>::iterator::iterator(T* ptr)
	: ptr{ptr}
{}

template <typename T>
vector<T>::iterator::iterator(iterator& rhv)
	: ptr{rhv.ptr}
{}

template <typename T>
vector<T>::iterator::iterator(iterator&& rhv)
	: ptr{std::move(rhv.ptr)}
{
	rhv.ptr = nullptr;
}

template <typename T>
typename vector<T>::iterator&
vector<T>::iterator::operator=(iterator& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
	}
	return *this;
}

template <typename T>
typename vector<T>::iterator&
vector<T>::iterator::operator=(iterator&& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
	return *this;
}

template <typename T>
typename vector<T>::reference
vector<T>::iterator::operator[](size_t index)
{
	return *(ptr + index);
}

template <typename T>
typename vector<T>::reference
vector<T>::iterator::operator[](size_t index) const
{
	return *(ptr + index);
}

// pre-fix
template <typename T>
typename vector<T>::iterator&
vector<T>::iterator::operator++()
{
	*ptr++;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator++(int)
{
	pointer tmp = ptr;
	*ptr++;
	return vector<T>::iterator(tmp);
}

// pre-fix
template <typename T>
typename vector<T>::iterator&
vector<T>::iterator::operator--()
{
	*ptr--;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator--(int)
{
	pointer tmp = ptr;
	*ptr--;
	return vector<T>::iterator(tmp);
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator+(int ind)
{
	return iterator(ptr + ind);
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator-(int ind)
{
	return iterator(ptr - ind);
}

template <typename T>
typename vector<T>::reference
vector<T>::iterator::operator*()
{
	return *ptr;
}

template <typename T>
typename vector<T>::pointer
vector<T>::iterator::operator->()
{
	return ptr;
}

template <typename T>
bool
vector<T>::iterator::operator==(const iterator& other) const
{
	return (ptr == other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::iterator::operator!=(const iterator& other) const
{
	return (ptr == other.ptr ? false : true);
}

template <typename T>
bool
vector<T>::iterator::operator<(const iterator& other) const
{
	return (ptr < other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::iterator::operator<=(const iterator& other) const
{
	return (ptr <= other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::iterator::operator>(const iterator& other)const
{
	return (ptr > other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::iterator::operator>=(const iterator& other) const
{
	return (ptr >= other.ptr ? true : false);
}


// --------------------------------------------------

// Const Reverse Iterator class

template <typename T>
vector<T>::const_reverse_iterator::
const_reverse_iterator() = default;

template <typename T>
vector<T>::const_reverse_iterator::
const_reverse_iterator(pointer ptr)
	: ptr{ptr}
{}

template <typename T>
vector<T>::const_reverse_iterator::
const_reverse_iterator(const const_reverse_iterator& rhv)
	: ptr{rhv.ptr}
{}

template <typename T>
vector<T>::const_reverse_iterator::
const_reverse_iterator(const_reverse_iterator&& rhv)
	: ptr{std::move(rhv.ptr)}
{
	rhv.ptr = nullptr;
}

template <typename T>
typename vector<T>::const_reverse_iterator&
vector<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
	}

	return *this;
}

template <typename T>
typename vector<T>::const_reverse_iterator&
vector<T>::const_reverse_iterator::operator=(const_reverse_iterator&& rhv)
{
	if ( this != &rhv )
	{
		ptr = std::move(rhv.ptr);
		rhv.ptr = nullptr;
	}

	return *this;
}

// template <typename T>
// typename vector<T>::const_reference
// vector<T>::const_reverse_iterator::operator[](size_t index)
// {
// 	return vector<T>::const_reverse_iterator(ptr - index);
// }

template <typename T>
typename vector<T>::const_reference
vector<T>::const_reverse_iterator::operator[](size_t index) const
{
	return vector<T>::const_reverse_iterator(ptr - index);
}

// pre-fix
template <typename T>
typename vector<T>::const_reverse_iterator&
vector<T>::const_reverse_iterator::operator--()
{
	*ptr++;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::const_reverse_iterator::operator--(int)
{
	pointer tmp = ptr;
	*ptr++;
	return vector<T>::const_reverse_pointer(tmp);
}

// pre-fix
template <typename T>
typename vector<T>::const_reverse_iterator&
vector<T>::const_reverse_iterator::operator++()
{
	*ptr--;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::const_reverse_iterator::operator++(int)
{
	pointer tmp = ptr;
	*ptr--;
	return vector<T>::const_reverse_pointer(tmp);
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::const_reverse_iterator::operator+(int ind)
{
	return const_reverse_iterator(ptr - ind);
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::const_reverse_iterator::operator-(int ind)
{
	return const_reverse_iterator(ptr + ind);
}

template <typename T>
typename vector<T>::const_reference
vector<T>::const_reverse_iterator::operator*()
{
	return *ptr;
}

template <typename T>
typename vector<T>::const_pointer
vector<T>::const_reverse_iterator::operator->()
{
	return ptr;
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator==(const const_reverse_iterator& other) const
{
	return (ptr == other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator!=(const const_reverse_iterator& other) const
{
	return (ptr == other.ptr ? false : true);
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator<(const const_reverse_iterator& other) const
{
	return (ptr > other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator<=(const const_reverse_iterator& other) const
{
	return (ptr >= other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator>(const const_reverse_iterator& other) const
{
	return (ptr < other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::const_reverse_iterator::
operator>=(const const_reverse_iterator& other) const
{
	return (ptr <= other.ptr ? true : false);
}


// --------------------------------------------------

// Reverse Iterator class

template <typename T>
vector<T>::reverse_iterator::reverse_iterator() = default;

template <typename T>
vector<T>::reverse_iterator::
reverse_iterator(pointer ptr)
	: ptr{ptr}
{}

template <typename T>
vector<T>::reverse_iterator::
reverse_iterator(const reverse_iterator& rhv)
	: ptr{rhv.ptr}
{}

template <typename T>
vector<T>::reverse_iterator::
reverse_iterator(reverse_iterator&& rhv)
	: ptr{std::move(rhv.ptr)}
{
	rhv.ptr = nullptr;
}

template <typename T>
typename vector<T>::reverse_iterator&
vector<T>::reverse_iterator::operator=(const reverse_iterator& rhv)
{
	if ( this != &rhv )
	{
		ptr = rhv.ptr;
	}

	return *this;
}

template <typename T>
typename vector<T>::reverse_iterator&
vector<T>::reverse_iterator::operator=(reverse_iterator&& rhv)
{
	if ( this != &rhv )
	{
		ptr = std::move(rhv.ptr);
		rhv.ptr = nullptr;
	}

	return *this;
}

template <typename T>
typename vector<T>::reference
vector<T>::reverse_iterator::operator[](size_t index)
{
	return vector<T>::reverse_iterator(ptr - index);
}

template <typename T>
typename vector<T>::reference
vector<T>::reverse_iterator::operator[](size_t index) const
{
	return vector<T>::reverse_iterator(ptr - index);
}

// pre-fix
template <typename T>
typename vector<T>::reverse_iterator&
vector<T>::reverse_iterator::operator--()
{
	*ptr++;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::reverse_iterator
vector<T>::reverse_iterator::operator--(int)
{
	pointer tmp = ptr;
	*ptr++;
	return vector<T>::reverse_pointer(tmp);
}

// pre-fix
template <typename T>
typename vector<T>::reverse_iterator&
vector<T>::reverse_iterator::operator++()
{
	*ptr--;
	return *this;
}

// post-fix
template <typename T>
typename vector<T>::reverse_iterator
vector<T>::reverse_iterator::operator++(int)
{
	pointer tmp = ptr;
	*ptr--;
	return vector<T>::reverse_pointer(tmp);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::reverse_iterator::operator+(int ind)
{
	return reverse_iterator(ptr - ind);
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::reverse_iterator::operator-(int ind)
{
	return reverse_iterator(ptr + ind);
}

template <typename T>
typename vector<T>::reference
vector<T>::reverse_iterator::operator*()
{
	return *ptr;
}

template <typename T>
typename vector<T>::pointer
vector<T>::reverse_iterator::operator->()
{
	return ptr;
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator==(const reverse_iterator& other) const
{
	return (ptr == other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator!=(const reverse_iterator& other) const
{
	return (ptr == other.ptr ? false : true);
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator<(const reverse_iterator& other) const
{
	return (ptr > other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator<=(const reverse_iterator& other) const
{
	return (ptr >= other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator>(const reverse_iterator& other) const
{
	return (ptr < other.ptr ? true : false);
}

template <typename T>
bool
vector<T>::reverse_iterator::
operator>=(const reverse_iterator& other) const
{
	return (ptr <= other.ptr ? true : false);
}

#endif