#include <list>
#include "map.hpp"
#include "common.hpp"
#include <map>

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


#define T1 int
#define T2 int

typedef pair<const T1, T2> T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	map<T1, T2> mp(lst.begin(), lst.end());
	map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

	map<T1, T2> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	map<T1, T2> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	std::cout << "\t-- PART ONE --" << std::endl;

//	std::cout << "size is " << mp.size() << std::endl;

	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();
	mp_copy.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
//	std::cout << "size is " << mp.size() << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);
	return (0);
}
