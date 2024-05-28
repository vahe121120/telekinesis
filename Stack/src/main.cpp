#include <iostream>
#include "../headers/stack.h"

using namespace std;

template <typename T, typename Container>
void print(const stack<T, Container>& obj)
{
    for ( int i = 0; i < obj.size(); ++i )
    {
        cout << obj[i] << " ";
    }
    cout << endl << endl;
}

int main()
{
    stack<int> obj(3, 1);
    cout << "Printing obj(3, 1)..." << endl;
    print(obj);

    stack<int> v = {1, 2, 3};
    cout << "Printing v = {1, 2, 3}..." << endl;
    print(v);

    cout << "obj = v" << endl;
    obj = v;
    cout << "obj = ";
    print(obj);

    cout << "v = {23, 22, 21}" << endl;
    v = {23, 22, 21};
    print(v);

    cout << "Comparing 'obj == v'" << endl;
    if ( obj == v )
        cout << "Equal" << endl;
    else
        cout << "Not Equal" << endl;

    obj.swap(v);
    cout << "Printing obj.swap(v)..." << endl;
    cout << "obj = ";
    print(obj);

    cout << "v = ";
    print(v);

    return 0;
}