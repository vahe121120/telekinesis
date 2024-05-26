#include <iostream>
#include "vector.hpp"

template <typename T>
void print(const vector<T>& obj)
{
	// std::cout << std::endl;
	for ( const auto i : obj )
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
}

int main()
{
	vector<int> a = {1, 2 ,3};
	std::cout << "vector a = ";
	print(a);
	
	vector<int> b = {3, 2, 1};
	std:: cout << "vector b = ";
	print(b);

	a = b;
	std::cout << "vector 'a' assigned vector 'b'" << std::endl;
	std::cout << "vector a = ";
	print(a);

	vector<int> obj1 = {11, 22, 33, 44};
	std::cout << "vector obj1 = ";
	print(obj1);

	vector<int> obj2(obj1);
	std::cout << "vector obj2 after copy ctor = ";
	print(obj2);

	obj2.resize(6, 87);
	std::cout << "vector obj2 after resizing = ";
	print(obj2);


	std::cout << "vector cob = ";
	vector<int> cob = {5, 7, 8};
	print(cob);

	std::cout << "insert {pos, count, value} to 'cob'" << std::endl;
	vector<int>::const_iterator it = cob.cbegin() + 1;
	cob.insert(it, 2);
	print(cob);

	std::cout << "vector 'cob' after erase(pos) = ";
	vector<int>::const_iterator iter = cob.cbegin() + 3;
	cob.erase(iter);
	print(cob);

	vector<int> myVec = {55, 44, 66};
	std::cout << "Printing myVec = ";
	print(myVec);


	std::cout << "myVec after erase(first, last) = ";
	vector<int>::const_iterator start = myVec.cbegin() + 2;
	vector<int>::const_iterator end = myVec.cend();
	myVec.erase(start, end);
	print(myVec);

	std::cout << "myVec after insert(pos, first, last) = ";
	vector<int>::const_iterator pos = myVec.cbegin() + 1;
	vector<int>::iterator first = cob.begin();
	vector<int>::iterator last = cob.begin() + 2;
	myVec.insert<vector<int>::iterator>(pos, first, last);
	print(myVec);

	return 0;
}
