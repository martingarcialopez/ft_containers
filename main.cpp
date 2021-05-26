#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

using namespace std;

int main() {

    ft::vector<int>     test;
    vector<int>         vec;

    //test[0] = 3;
    //test[1] = 2;
    //test[2] = 1;
    
    test.push_back(42);
    test.push_back(21);
    test.push_back(10);
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    test.push_back(1);

    test.pop_back();
    test.pop_back();
    test.pop_back();
    test.pop_back();
    test.pop_back();

    for (int i = 0; i < test.size(); i++) {
        cout << test[i] << endl;
    }

    return 0;
}
