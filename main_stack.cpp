#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include "stack.hpp"
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
    std::cout << "..................Constructors......................" << std::endl << std::endl;
    {
        std::deque<int> mydeque (3,100);          // deque with 3 elements
        std::vector<int> myvector (2,200);        // vector with 2 elements
        stack<int> first;                    // empty stack
        stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque
        stack<int,std::vector<int> > third;  // empty stack using vector
        stack<int,std::vector<int> > fourth (myvector);
        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
    }
    std::cout << "...................Empty..................." << std::endl << std::endl;
    {
        stack<int> mystack;
        int sum (0);
        for (int i=1;i<=10;i++) mystack.push(i);
        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }
        std::cout << "total: " << sum << '\n';
    }
    std::cout << ".................Size....................." << std::endl << std::endl;
    {
        stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';
        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';
        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
    }
    std::cout << "..................Top..................." << std::endl << std::endl;
    {
        stack<int> mystack;
        mystack.push(10);
        mystack.push(20);
        mystack.top() -= 5;
        std::cout << "mystack.top() is now " << mystack.top() << '\n';
    }
    std::cout << "...............Push......................" << std::endl << std::endl;
    {
        stack<int> mystack;
        for (int i=0; i<5; ++i) mystack.push(i);
        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
    }
    std::cout << "....................Pop..................." << std::endl << std::endl;
    {
        stack<int> mystack;
        for (int i=0; i<5; ++i) mystack.push(i);
        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';
    }
    return 0;
}
