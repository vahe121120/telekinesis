#include <iostream>
#include <string>
#include "../headers/queue.h"

using namespace std;


template <typename T, typename Container>
void print(queue<T, Container> list)
{
    size_t size = list.size();
    for ( int i = 0; i < size; ++i )
    {
        cout << list[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "emplace()" << endl;
    queue<string> qwu;
    qwu.emplace("Hello,");
    qwu.emplace("I'm");
    qwu.emplace("Vahe!");

    print(qwu);

    cout << endl << "list 1" << endl;
    queue<int> list = {1, 2, 3};
    print(list);

    queue<int> list2 = {5, 8, 7, 55, 4, 1, 3, 11, 23};
    cout << endl << "list 2" << endl;
    print(list2);

    cout << endl << "pushing 23 to list 1" << endl;
    list.push(23);

    cout << endl << "-----------------" << endl
    << "swapping list 1 and list 2" << endl;
    list.swap(list2);
    cout << "Printing list 1..." << endl;
    print(list);

    cout << "Printing list 2..." << endl;
    print(list2);
    
    cout << "pop() from list 2" << endl;
    list2.pop();

    cout << endl << "--------------- push_range() list 2 -----------------" << endl;
    list2.push_range(11, 22, 33);
    print(list2);
 
    return 0;
}