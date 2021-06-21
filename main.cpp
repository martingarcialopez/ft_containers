#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

#ifdef STD
 using namespace std;
 #define NAMESPACE_DEFINED
#endif

#ifdef FT
 using namespace ft;
 #define NAMESPACE_DEFINED
#endif

#ifndef NAMESPACE_DEFINED
 using namespace ft;
#endif

int main() {
    
    vector<int> foo(3);

    std::cout << foo.size() << std::endl;

    return 0;

}
