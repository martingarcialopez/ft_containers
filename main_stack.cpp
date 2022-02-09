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


	stack<int, ft::vector<int> >	s;

	s.push(7);
	s.push(8);
	s.push(9);

	std::cout << "s.size() is " << s.size() << std::endl;
	if (s.empty())
		std::cout << "s is empty" << std::endl;
	else
		std::cout << "s is not empty" << std::endl;

	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	s.pop();

	std::cout << "s.size() is " << s.size() << std::endl;
	if (s.empty())
		std::cout << "s is empty" << std::endl;
	else
		std::cout << "s is not empty" << std::endl;



	return 0;
}
