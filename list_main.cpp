#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "list.hpp"

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

    ft::list<int> a;
    ft::list<int> * ptr = &a;

    a.push_front(1);
    a.push_front(2);
    a.push_front(3);
    a.push_front(4);


    ptr = ptr->next;

    //for (int i = 0; i < 10; i++) {
    while (ptr->data != NULL) {
        if (ptr->data)
            std::cout << *ptr->data << std::endl;
        else
            std::cout << ptr->data << std::endl;
        ptr = ptr->next;
    }

    return 0;
}
