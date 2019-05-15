#include "./include/RedBlackTree.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#define LIM 20

int main(int arcv, char *argv[])
{
	std::srand(LIM);
    std::vector<int> random;
	for(int i = 0; i<LIM; i++)
		random.push_back(i);
	//std::random_shuffle ( random.begin(), random.end() );
    int balanced = 1;
    RedBlackTree<int, int> rbt;
    int i = 1;
    for(auto e : random)
	{
        //if(i == 6) break;
        //std::cout << i << std::endl;
        rbt.insert(e,e);
       
        //i++;
	}
    rbt.printTree(rbt.root_get());


    std::random_shuffle ( random.begin(), random.end() );
    for(auto e : random)
    {
        if(i == 5) break;
        std::cout <<"tolgo " << e << std::endl;
        rbt.remove(e);
        i++;
    }


     if(rbt.isRBvalid(rbt.root_get()) != true){
            balanced = 0;
        }

    rbt.printTree(rbt.root_get());

    if(balanced)
        std::cout<< "Bravo!\n" << std::endl;
    else
        std::cout<< "Buuu!\n" << std::endl;


}
