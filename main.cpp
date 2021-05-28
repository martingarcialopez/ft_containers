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




  vector<int> first;
  vector<int> second;
  vector<int> third;

  first.assign (7u,100);             // 7 ints with a value of 100

  vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  for (int i = 0; i < second.size(); i++)
    std::cout << second[i] << " ";
  std::cout << std::endl;

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';




    return 0;
}
