#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "../BinaryTreeRec.h"
#include <fstream>

int main(int arcv, char *argv[])
{

	std::srand(0);
	const size_t N = (arcv<2) ? 10000 : atoi(argv[1]);

	BinaryTree<const int, double> linked_list_tree;

	
	//////////// Initializing tree ////////////
	std::cout << N << ";";

		//std::cout << "initializing linked_list_tree . . ." << std::endl;
		for(int i = 0; i<N; i++)
		{
			linked_list_tree.insert(i,i);
		}

	//////////// Performance measuring ////////////

	// reshuffling for random access
	std::vector<double> random_permutation_vector;
	for(int i = 0; i<N; i++)
		random_permutation_vector.push_back(i);
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.end() );

	// just for initializing them
	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();

	//
	std::vector<double> container;
	

	//LINKED LIST TREE
		begin = std::chrono::high_resolution_clock::now();
		for(auto e : random_permutation_vector)
		{
			container.push_back(linked_list_tree[e]);
		}
		end = std::chrono::high_resolution_clock::now();
		total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
		std::cout << "LINKED_LIST_TREE: " << total/double(N) << std::endl;


	double s{0};
	for(double x: container)
		s+=x;

	
    return 0;
}
