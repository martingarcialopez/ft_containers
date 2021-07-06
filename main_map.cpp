#include "map.hpp"
#include <map>

using namespace ft;

int main() {

    map<char,int> first;
    first['a']=10;
    first['b']=30;
    first['c']=50;
    first['d']=70;

    std::cout << first['a'] << std::endl;
    std::cout << first['b'] << std::endl;
    std::cout << first['c'] << std::endl;
    std::cout << first['d'] << std::endl;
}
