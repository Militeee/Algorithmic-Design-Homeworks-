#include "./include/RedBlackTree.h"
#define __TESTBTFUN__
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#define LIM 1000

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
		rbt.insert(e,e);
        if(rbt.isBalanced(rbt.root_get()) == true){
            balanced = 0;
            break;
        }
	}

    if(balanced)
        std::cout<< "Bravo!\n" << std::endl;
    else
        std::cout<< "Buuu!\n" << std::endl;

}
