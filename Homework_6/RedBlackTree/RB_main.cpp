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
        //if(i == 4) break;
        //std::cout << i << std::endl;
        rbt.insert(e,e);
       
	}
    rbt.printTree(rbt.root_get());

     //if(rbt.isRBvalid(rbt.root_get()) != true){
     //       balanced = 0;
   // }


    if(balanced)
        std::cout<< "Insert corretto!\n" << std::endl;
    else
        std::cout<< "Insert non corretto !\n" << std::endl;

    balanced = 1;
    std::random_shuffle ( random.begin(), random.end() );
    for(auto e : random)
    {
        if(i == 10) break;
        std::cout <<"tolgo " << e << std::endl;
        rbt.remove(e);
        i++;
    }

    rbt.printTree(rbt.root_get());

    // if(rbt.isRBvalid(rbt.root_get()) != true){
     //       balanced = 0;
    //}


    if(balanced)
        std::cout<< "Remove corretto!\n" << std::endl;
    else
        std::cout<< "Remove non corretto!\n" << std::endl;


}
