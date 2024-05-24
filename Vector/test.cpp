#include <iostream>

using namespace std;

template <typename T>
class vector
{
	private:
		size_t len;
		size_t cap;
		T* arr;

	public:
		vector(size_t);
		vector(size_t, const T);
        vector(const vector&);
        const vector& operator=(const vector<T>&);
		~vector();
		
	public:
		const T& at(const size_t);
		void resize(size_t, const T);
		const T& front();
		const T& back();
	
	public:
		const T& insert(size_t, const T);
		void remove(size_t);
		void push_back(const T);
		void pop_back();

	public:
		void clear();
		bool empty();
		size_t size();
		size_t capacity();
};

template <typename T>
vector<T>::vector(size_t s)
	: len{s}
	, cap{s}
{
	if ( !s )
		throw 1;

	if ( !arr )
	{
		arr = new T [s];
	}
}

template <typename T>
vector<T>::vector(size_t s, const T val)
	: len{s}
	, cap{s}
{
	if ( s )
	{
		arr = new T [cap];
	}

	for (int i = 0; i < s; ++i)
	{
		arr[i] = val;
	}
}

// Copy constructor
template <typename T>
vector<T>::vector(const vector& rhv)
{
	if ( this != rhv )
	{
		this->len = rhv.len;
		this->cap = rhv.cap;

		delete [] this->arr;
		arr = nullptr;
		arr = new T [cap];

		for (int i = 0; i < this->len; ++i)
		{
			this->arr[i] = rhv.arr[i];
		}
	}
}

template <typename T>
vector<T>::~vector()
{
	for (int i = this->len; i != -1; --i)
	{
		arr[i] = 0;
	}

	this->len = 0;
	this->cap = 0;
		

	delete [] arr;
}

template <typename T>
const vector<T>& vector<T>::operator=(const vector<T>& ob)
{
        if ( this != ob )
        {
                this->len = ob.len;
                this->cap = ob.cap;

		if ( arr )
                {
                        delete [] arr;
                        arr = new T [this->cap];
                }
 
                for (int i = 0; i < this->len; ++i)
                {
                        this->arr[i] = ob.arr[i];
                }
	} 

        return this;
}

template <typename T>
const T& vector<T>::at(const size_t index)
{
	if ( !index ) throw;
	return arr[index];
}

template <typename T>
void vector<T>::resize(size_t s, const T val)
{
	if ( s == this->len ) return;

	if ( s > this->len )
	{
		if ( s > this->cap )
			cap = s * 2;
		T* ptr = new T [cap];

		for (int i = 0; i < this->len; ++i)
		{
			ptr[i] = this->arr[i];
		}

		this->arr = ptr;
		delete [] ptr;
		this->len = s;
	}
	else
	{
		this->len = s;
	}
}

template <typename T>
const T& vector<T>::front()
{
	if ( this->len )
		return arr[0];
	throw;
}

template <typename T>
const T& vector<T>::back()
{
	if ( this->len )
		return arr[len - 1];
	throw;
}

template <typename T>
const T& vector<T>::insert(size_t index, const T val)
{
	if ( index == 0 || index >= this->len )
		throw;

	this->len++;

	if ( this->len >= this->cap )
		this->cap *= 2;

	T* ptr = new T [this->len];

	for (int i = 0, j = 0; i < this->len; ++i, ++j)
	{
		if ( i == index )
		{
			ptr[i] = val;
			--j;
			continue;
		}

		ptr[i] = arr[j];
	}

	delete [] arr;
	arr = ptr;
	delete [] ptr;
}

template <typename T>
void vector<T>::remove(size_t index)
{
	if ( index == 0 || index >= this->len ) throw;

	T* ptr = new T [this->len - 1];

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

/* void push_back(const T&); */

template <typename T>
void vector<T>::push_back(const T val)
{
	this->len++;
	if ( this->len >= this->cap )
		cap *= 2;
	this->arr[len - 1] = val;
}

template <typename T>
void vector<T>::pop_back()
{
	if ( this->len - 1 )
	{
		this->len--;
	}
}

template <typename T>
void vector<T>::clear()
{
	if ( arr )
	{
		delete [] arr;
		arr = nullptr;
	}
}

template <typename T>
bool vector<T>::empty()
{
	if ( this->len ) return 0;
	return 1;
}

template <typename T>
size_t vector<T>::size()
{
	return this->len;
}

template <typename T>
size_t vector<T>::capacity()
{
	return this->cap;
}

int main()
{
	vector<int> arr{5};

	// for (int i = 0; i < 5; ++i)
	// {
	// 	arr.at(i) = (i + 1);
	// }

	for (int i = 0; i < 5; ++i)
	{
		cout << arr.at(i) << " ";
	}

	cout << endl;

	return 0;
}
