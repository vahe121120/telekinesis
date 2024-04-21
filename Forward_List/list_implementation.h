#ifndef __LIST_IMPLEMENTATION__
#define __LIST_IMPLEMENTATION__

#include "forward_list.hpp"
#include <initializer_list>

template <typename T>
forward_list<T>::
forward_list()
	: forward_list(0, value_type{})
{}

template <typename T>
forward_list<T>::
forward_list(size_type size)
	: forward_list(size, value_type{})
{}

template <typename T>
forward_list<T>::
forward_list(size_type size, value_type val)
	: head{nullptr}
{
	if ( !size )
	{
		return;
	}
	
	head = new Node;
	Node* ptr = head;
	
	while ( size )
	{
		ptr->data = val;
		
		if ( size != 1 )
		{
			ptr->next = new Node;
			ptr = ptr->next;
		}
		--size;
	}
	ptr->next = nullptr;
}

template <typename T>
forward_list<T>::
forward_list(std::initializer_list<value_type> l)
	: head{nullptr}
{
	size_type size = l.size();

	if ( !size )
	{
		return;
	}

	head = new Node;
	Node* ptr = head;

	while ( size )
	{
		if ( size != 1 )
		{
			ptr->next = new Node;
			ptr = ptr->next;
		}
		--size;
	}

	ptr->next = nullptr;
	ptr = head;

	for ( auto value : l )
	{
		ptr->data = value;
		ptr = ptr->next;
	}
}

template <typename T>
forward_list<T>::
forward_list(self_referenceL rhv)
{
	head = new Node;
	Node* ptr = head;
	Node* rhvptr = rhv.head;

	while ( rhvptr->next )
	{
		ptr->data = rhvptr->data;
		ptr->next = new Node;
		ptr = ptr->next;
		rhvptr = rhvptr->next;
	}
	ptr->data = rhvptr->data;
	ptr->next = nullptr;
}

template <typename T>
forward_list<T>::
forward_list(self_referenceR rhv)
	: head{rhv.head}
{
	rhv.head = nullptr;
}

template <typename T>
forward_list<T>::
~forward_list()
{
	clear();
}

template <typename T>
forward_list<T>& forward_list<T>::
operator=(self_referenceL rhv)
{
	if ( this != &rhv )
	{
		this->clear();

		head = new Node;
		Node* ptr = head;
		Node* rhvptr = rhv.head;

		while ( rhvptr->next )
		{
			ptr->data = rhvptr->data;
			ptr->next = new Node;
			ptr = ptr->next;
			rhvptr = rhvptr->next;
		}
		ptr->data = rhvptr->data;
		ptr->next = nullptr;
	}

	return *this;
}

template <typename T>
forward_list<T>& forward_list<T>::
operator=(self_referenceR rhv)
{
	if ( this != &rhv )
	{
		this->head = rhv.head;
		rhv.head = nullptr;
	}

	return *this;
}

template <typename T>
T& forward_list<T>::
operator[](size_type index)
{
	Node* ptr = head;
    size_type count = 0;

    while ( count >= 0 )
    {
        if ( count == index )
        {
          return ptr->data;  
        }
        //if ( ptr->next )
          ptr = ptr->next;

        ++count;
    }

    return ptr->data;
}

template <typename T>
const T& forward_list<T>::
operator[](size_type index) const
{
	Node* ptr = head;
    size_type count = 0;

    while ( count >= 0 )
    {
        if ( count == index )
        {
          return ptr->data;  
        }
        //if ( ptr->next )
          ptr = ptr->next;

        ++count;
    }

    return ptr->data;
}

template <typename T>
T& forward_list<T>::
at(const size_type index)
{
	Node* ptr = head;
	size_type count{};

	while ( ptr )
	{
		++count;
		ptr = ptr->next;
	}

	if ( index > count )
	{
		throw 1;
	}

	ptr = head;
	for ( int i = 0; i < count; ++i )
	{
		if ( i == index )
		{
			return ptr->data;
		}
		ptr = ptr->next;
	}
}

template <typename T>
void forward_list<T>::
resize(const size_type size)
{
	resize(size, value_type{});
}

template <typename T>
void forward_list<T>::
resize(const size_type size, const value_type value)
{
    Node* ptr = head;
    size_type count{};

    while ( ptr )
    {
        ++count;
        if ( ptr->next )
          ptr = ptr->next;
        else
          break;
    }

    if ( size > count )
    {
        for ( int i = count; i < size; ++i )
        {
            ptr->next = new Node;
            ptr = ptr->next;
            ptr->data = value;
        }
        ptr->next = nullptr;
    }
    else
    {
        ptr = head;
        while ( count > size ) {
        	for ( int i = count; i >= size - 1; --i )
          	{
            	if ( ptr->next->next )
              	{
	                ptr = ptr->next;
    		    }
              	else
              	{
                	delete ptr->next;
                	ptr->next = nullptr;
                	ptr = head;
              	}
          	}
          	--count;
        }
    }
}

template <typename T>
T& forward_list<T>::
front()
{
	return head->data;
}

template <typename T>
T& forward_list<T>::
back()
{
	Node* ptr = head;
	while ( ptr->next )
	{
		ptr = ptr->next;
	}

	return ptr->data;
}

template <typename T>
void forward_list<T>::
insert(const size_type index, const value_type value)
{
	Node* ptr = head;
    size_type count = this->size();

	if ( index > count )
	{
		return;
	}

    for ( int i = 0; i < count; ++i )
    {
        if ( i == index - 1 )
        {
            Node* tmp = ptr->next;
        	ptr->next = new Node;
			ptr->next->data = value;
            ptr->next->next = tmp;
            break;
        }
        ptr = ptr->next;
    }
}

template <typename T>
void forward_list<T>::
remove(size_type index)
{
	Node* ptr = head;
    size_type count = this->size();

	if ( index >= count )
	{
		return;
	}

    for ( int i = 0; i < count; ++i )
    {
        if ( i == index - 1 )
        {
            Node* tmp = ptr->next->next;
            delete ptr->next;
            ptr->next = tmp;
            break;
        }
        ptr = ptr->next;
    }
}

template <typename T>
void forward_list<T>::
push_back(const value_type value)
{
	Node* ptr = head;
	while ( ptr->next )
	{
		ptr = ptr->next;
	}
	ptr->next = new Node;
	ptr = ptr->next;
	ptr->data = value;
	ptr->next = nullptr;
}

template <typename T>
void forward_list<T>::
pop_back()
{
	Node* ptr = head;
	while ( ptr->next->next )
	{
		ptr = ptr->next;
	}
	delete ptr->next;
	ptr->next = nullptr;
}

template <typename T>
T* forward_list<T>::
data()
{
	return head;
}


template <typename T>
void forward_list<T>::
recap(size_type cap)
{
	Node* ptr = head;
	size_type size = this->size();

	while ( ptr )
    {
        if ( ptr->next )
          ptr = ptr->next;
        else
          break;
    }

	if ( cap > size )
	{
		for ( int i = size; i < cap; ++i )
		{
			ptr->next= new Node;
			ptr = ptr->next;
		}
		ptr->next = nullptr;
	}
	else
	{
		resize(size);
	}
}


template <typename T>
void forward_list<T>::
clear()
{
	Node* ptr = head;

    while ( head )
    {
        if ( ptr->next->next )
        {
            ptr = ptr->next;
            continue;
        }

        ptr->next->data = 0;
        delete ptr->next;
        ptr->next = nullptr;
        ptr = head;
        
        if ( !head->next )
        {
          head->data = 0;
          delete head;
          ptr = nullptr;
          head = nullptr;
        }
    }
}

template <typename T>
bool forward_list<T>::
empty()
{
	return !head;
}

template <typename T>
size_t forward_list<T>::
size()
{
	Node* ptr = head;
	size_type count{};

	while ( ptr )
	{
		++count;
		ptr = ptr->next;
	}

	return count;

}

template <typename T>
size_t forward_list<T>::
capacity()
{
	size();
}


#endif
