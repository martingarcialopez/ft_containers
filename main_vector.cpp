#include <iostream>
#include <string>
#include <vector>
#include <list>
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

    //////////////    CONSTRUCTORS     ///////////////////////////////////

	{
  		vector<int> first;                                // empty vector of ints
  		vector<int> second (4,100);                       // four ints with value 100
  		vector<int> third (second.begin(),second.end());  // iterating through second
  		vector<int> fourth (third);                       // a copy of third

  		// the iterator constructor can also be used to construct from arrays:
  		int myints[] = {16,2,77,29};
  		vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  		std::cout << "The contents of first are:";
  		for (vector<int>::iterator it = first.begin(); it != first.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
  		std::cout << "The contents of second are:";
  		for (vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
  		std::cout << "The contents of third are:";
  		for (vector<int>::iterator it = third.begin(); it != third.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
  		std::cout << "The contents of fourth are:";
  		for (vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
  		std::cout << "The contents of fifth are:";
  		for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}
  	//////////////////    OPERATOR=    /////////////////////////////////////

	{
  		vector<int> foo (3,0);
  		vector<int> bar (5,0);

  		bar = foo;
  		foo = vector<int>();

  		std::cout << "Size of foo: " << int(foo.size()) << '\n';
  		std::cout << "Size of bar: " << int(bar.size()) << '\n';
	}


  	/////////////////    ITERATORS       //////////////////////////////////

  	// begin
	{
  		vector<int> myvector;
  		for (int i=1; i<=5; i++) myvector.push_back(i);

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	// end
	{
  		vector<int> myvector;
  		for (int i=1; i<=5; i++) myvector.push_back(i);

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	// rbegin
	{
  		vector<int> myvector (5);  // 5 default-constructed ints

  		int i=0;

  		vector<int>::reverse_iterator rit = myvector.rbegin();
  		for (; rit!= myvector.rend(); ++rit)
    		*rit = ++i;

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	// rend
	{
  		vector<int> myvector (5);  // 5 default-constructed ints

  		vector<int>::reverse_iterator rit = myvector.rbegin();

  		int i=0;
  		for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    		*rit = ++i;

  		std::cout << "myvector contains:";
  		for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	// casting iterators
	{
  		vector<int> myvector;
  		for (int i=1; i<=5; i++) myvector.push_back(i);

  		vector<int>::iterator it = myvector.begin();
  		vector<int>::iterator const_it = it;

  		std::cout << "myvector contains:";
  		for (; const_it != myvector.end(); ++const_it)
    		std::cout << ' ' << *const_it;
  		std::cout << '\n';
	}

  	// bidirectional iterators

	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	vector<int> vct(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

  		std::cout << "The contents of vector are:";
  		for (vector<int>::iterator it = vct.begin(); it != vct.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	std::cout << vct.size() << std::endl;
	return (0);


  	/////////////////     CAPACITY               /////////////////////////////////

  	// size
	{
  		vector<int> myints;
  		std::cout << "0. size: " << myints.size() << '\n';

  		for (int i=0; i<10; i++) myints.push_back(i);
  		std::cout << "1. size: " << myints.size() << '\n';

  		myints.insert (myints.end(),10,100);
  		std::cout << "2. size: " << myints.size() << '\n';

  		myints.pop_back();
  		std::cout << "3. size: " << myints.size() << '\n';
	}

  	// max_size
	{
  		vector<int> myvector;

  		// set some content in the vector:
  		for (int i=0; i<100; i++) myvector.push_back(i);

  		std::cout << "size: " << myvector.size() << "\n";
  		std::cout << "capacity: " << myvector.capacity() << "\n";
  		std::cout << "max_size: " << myvector.max_size() << "\n";
	}

  	// resize
	{
  		vector<int> myvector;

  		// set some initial content:
  		for (int i=1;i<10;i++) myvector.push_back(i);

  		myvector.resize(5);
  		myvector.resize(8,100);
  		myvector.resize(12);

  		std::cout << "myvector contains:";
  		for (uint i=0;i<myvector.size();i++)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';
	}

  	// capacity
	{
  		vector<int> myvector;

  		// set some content in the vector:
  		for (int i=0; i<100; i++) myvector.push_back(i);

  		std::cout << "size: " << (int) myvector.size() << '\n';
  		std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  		std::cout << "max_size: " << (int) myvector.max_size() << '\n';
	}

  	// empty
	{
  		vector<int> myvector;
  		int sum (0);

  		for (int i=1;i<=10;i++) myvector.push_back(i);

  		while (!myvector.empty())
  		{
     		sum += myvector.back();
     		myvector.pop_back();
  		}

  		std::cout << "total: " << sum << '\n';

	}

  	// reserve
	{
  		vector<int>::size_type sz;

  		vector<int> foo;
  		sz = foo.capacity();
  		std::cout << "making foo grow:\n";
  		for (int i=0; i<100; ++i) {
    		foo.push_back(i);
    		if (sz!=foo.capacity()) {
      			sz = foo.capacity();
      			std::cout << "capacity changed: " << sz << '\n';
    		}
  		}

  		vector<int> bar;
  		sz = bar.capacity();
  		bar.reserve(100);   // this is the only difference with foo above
  		std::cout << "making bar grow:\n";
  		for (int i=0; i<100; ++i) {
    		bar.push_back(i);
    		if (sz!=bar.capacity()) {
      			sz = bar.capacity();
      			std::cout << "capacity changed: " << sz << '\n';
    		}
  		}
	}


  	//////////////////    ELEMENT ACCESS    ///////////////////////////////////

  	// operator[]
	{
  		vector<int> myvector (10);   // 10 zero-initialized elements

  		vector<int>::size_type sz = myvector.size();

  		// assign some values:
  		for (unsigned i=0; i<sz; i++) myvector[i]=i;

  		// reverse vector using operator[]:
  		for (unsigned i=0; i<sz/2; i++)
  		{
    		int temp;
    		temp = myvector[sz-1-i];
    		myvector[sz-1-i]=myvector[i];
    		myvector[i]=temp;
  		}

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<sz; i++)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';
	}

  	// at
	{
    	vector<int> myvector (10);   // 10 zero-initialized ints

  		// assign some values:
  		for (unsigned i=0; i<myvector.size(); i++)
    		myvector.at(i)=i;

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); i++)
    		std::cout << ' ' << myvector.at(i);
  		std::cout << '\n';
	}

  	// front
	{
  		vector<int> myvector;

  		myvector.push_back(78);
  		myvector.push_back(16);

  		// now front equals 78, and back 16

  		myvector.front() -= myvector.back();

  		std::cout << "myvector.front() is now " << myvector.front() << '\n';

	}

  	// back
	{
  		vector<int> myvector;

  		myvector.push_back(10);

  		while (myvector.back() != 0)
  		{
    		myvector.push_back ( myvector.back() -1 );
  		}

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size() ; i++)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';

	}


  	///////////////     MODIFIERS     ////////////////////////////////////////

  	// assign
	{
  		vector<int> first;
  		vector<int> second;
  		vector<int> third;

  		first.assign (7,100);             // 7 ints with a value of 100

  		vector<int>::iterator it;
  		it=first.begin()+1;

  		second.assign (it,first.end()-1); // the 5 central values of first

  		int myints[] = {1776,7,4};
  		third.assign (myints,myints+3);   // assigning from array.

  		std::cout << "Size of first: " << int (first.size()) << '\n';
  		std::cout << "Size of second: " << int (second.size()) << '\n';
  		std::cout << "Size of third: " << int (third.size()) << '\n';
	}

  	// push_back
	{
  		vector<int> myvector;
  		//int myint;

  		//std::cout << "Please enter some integers (enter 0 to end):\n";
		/*
  		   do {
    	   std::cin >> myint;
    	   myvector.push_back (myint);
  		   } while (myint);*/
  		myvector.push_back (3);
  		myvector.push_back (-2);
  		myvector.push_back (5);
  		myvector.push_back (7);
  		myvector.push_back (42);

  		std::cout << "myvector stores " << int(myvector.size()) << " numbers: ";
  		for (uint i = 0; i < myvector.size(); i++)
      		std::cout << myvector[i] << " ";
  		std::cout << std::endl;
	}

  	// pop_back
	{
  		vector<int> myvector;
  		int sum (0);
  		myvector.push_back (100);
  		myvector.push_back (200);
  		myvector.push_back (300);

  		while (!myvector.empty())
  		{
    		sum+=myvector.back();
    		myvector.pop_back();
  		}

  		std::cout << "The elements of myvector add up to " << sum << '\n';
	}

  	//insert
	{
  		vector<int> myvector (3,100);
  		vector<int>::iterator it;

  		it = myvector.begin();
  		it = myvector.insert ( it , 200 );

  		myvector.insert (it,2,300);

  		// "it" no longer valid, get a new one:
  		it = myvector.begin();

  		vector<int> anothervector (2,400);
  		myvector.insert (it+2,anothervector.begin(),anothervector.end());

  		int myarray [] = { 501,502,503 };
  		myvector.insert (myvector.begin(), myarray, myarray+3);

  		std::cout << "myvector contains:";
  		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	// erase
	{
  		vector<int> myvector;

  		// set some values (from 1 to 10)
  		for (int i=1; i<=10; i++) myvector.push_back(i);

  		// erase the 6th element
  		myvector.erase (myvector.begin()+5);

  		// erase the first 3 elements:
  		myvector.erase (myvector.begin(),myvector.begin()+3);

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); ++i)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';

	}

  	// swap
	{
  		vector<int> foo (3,100);   // three ints with a value of 100
  		vector<int> bar (5,200);   // five ints with a value of 200

  		foo.swap(bar);

  		std::cout << "foo contains:";
  		for (unsigned i=0; i<foo.size(); i++)
    		std::cout << ' ' << foo[i];
  		std::cout << '\n';

  		std::cout << "bar contains:";
  		for (unsigned i=0; i<bar.size(); i++)
    		std::cout << ' ' << bar[i];
  		std::cout << '\n';
	}

  	// clear
	{
  		vector<int> myvector;
  		myvector.push_back (100);
  		myvector.push_back (200);
  		myvector.push_back (300);

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); i++)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';

  		myvector.clear();
  		myvector.push_back (1101);
  		myvector.push_back (2202);

  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); i++)
    		std::cout << ' ' << myvector[i];
  		std::cout << '\n';
	}


  	///////////////     RELATIONAL OPERATORS    /////////////////////////////

	{
  		vector<int> foo (3,100);   // three ints with a value of 100
  		vector<int> bar (2,200);   // two ints with a value of 200

  		if (foo==bar) std::cout << "foo and bar are equal\n";
  		if (foo!=bar) std::cout << "foo and bar are not equal\n";
  		if (foo< bar) std::cout << "foo is less than bar\n";
  		if (foo> bar) std::cout << "foo is greater than bar\n";
  		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}



  	////////////////     SWAP (vector)         //////////////////////////////

	{
		//  unsigned int i;
  		vector<int> foo (3,100);   // three ints with a value of 100
  		vector<int> bar (5,200);   // five ints with a value of 200

  		foo.swap(bar);

  		std::cout << "foo contains:";
  		for (vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';

  		std::cout << "bar contains:";
  		for (vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
	}

  	return 0;

}
