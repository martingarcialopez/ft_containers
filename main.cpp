#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

using namespace std;

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


    vector<int> myvector (3u,100);
    vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert ( it , 200 );

    myvector.insert (it,2,300);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

/*    vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);
*/
    std::cout << "myvector contains:";
    for (it=myvector.begin(); it < myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';



    return 0;
}
