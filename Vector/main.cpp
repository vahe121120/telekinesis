#include <iostream>
#include "vector.hpp"

int main()
{
	vector<int> cob = {5, 7, 8};

	vector<int>::const_iterator it = cob.cbegin() + 1;
	cob.insert(it, 2, 1);

	for ( auto& val : cob )
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	// std::cout << "'Range based for' through our vector" << std::endl;
	// for ( auto& val : cob )
	// {
	// 	std::cout << val << " ";
	// }

	return 0;
}
