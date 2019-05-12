#include "./include/RedBlackTree.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#define LIM 10

int main(int arcv, char *argv[])
{
	std::srand(LIM);
    std::vector<double> random;
	for(int i = 0; i<LIM; i++)
		random.push_back(i);
	std::random_shuffle ( random.begin(), random.end() );
    int balanced = 1;
    RedBlackTree<const int, double> rbt;
    
    for(auto e : random)
	{
		std::cout << e << std::endl;
        rbt.insert(e,e);
        
        /*
        if(rbt.isRBvalid(rbt.root_get()) != true){
            balanced = 0;
            break;
        }
        */
        
	}

    if(balanced)
        std::cout<< "Bravo!\n" << std::endl;
    else
        std::cout<< "Buuu!\n" << std::endl;

    std::cout << rbt;

}
