#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

using namespace ft;

int main() {
    //    int     tab[]={1, 2, 3};
    /*
    //const ft::vector<int>     test = {1, 2, 3};

    vector<int>       test;

    test.push_back(42);
    test.push_back(21);
    test.push_back(10);
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    test.push_back(1);

    for (vector<int>::iterator it = test.begin(); it != test.end(); ++it)
    std::cout << *it << std::endl;
    std::cout << std::endl;

    //system("leaks a.out");
    */




  vector<int> foo (3,100);   // three ints with a value of 100
  vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";






    return 0;
}
