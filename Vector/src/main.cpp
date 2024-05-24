#include <iostream>
#include "vector.hpp"

int main()
{
	vector<int> cob = {5, 7, 8};

	std::cout << "insert {pos, count, value} using range based for" << std::endl;
	vector<int>::const_iterator it = cob.cbegin() + 1;
	cob.insert(it, 2, 1);

	for ( auto& val : cob )
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	std::cout << "vector assignment" << std::endl;
	vector<int> a = {1, 2 ,3};
	vector<int> b = {3, 2, 1};
	a = b;

	for ( auto& val : a )
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	return 0;
}
