#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

using namespace ft;

int main() {
//    int     tab[]={1, 2, 3};

    //const ft::vector<int>     test = {1, 2, 3};

    vector<int>       test;
    //ft::vector<int>   test;

    //test[0] = 3;
    //test[1] = 2;
    //test[2] = 1;
/*    
    test.push_back(42);
    test.push_back(21);
    test.push_back(10);
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    test.push_back(1);
*/
    /*test.pop_back();
    test.pop_back();
    test.pop_back();
    test.pop_back();
    test.pop_back();*/

    /*for (int i = 0; i < test.size(); i++) {
        cout << test[i] << endl;
    }*/

    //ft::vector<int>::const_reverse_iterator cit = test.rbegin();

    for (vector<int>::const_reverse_iterator it = test.rbegin(); it != test.rend() ; it+=1) {
        std::cout << *it << std::endl;
        //*it = *it + 1;

    }

    return 0;
}
