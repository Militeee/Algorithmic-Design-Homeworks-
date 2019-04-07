#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "BinaryTreeRec.h"

int main(int arcv, char *argv[])
{

	
	const int N1 = (arcv<2) ? 40000 : atoi(argv[1]); //size of the linked list tree
	const int N2 = (arcv<3) ? 2000000 : atoi(argv[2]); //size of the faster trees
	std::srand(N2);
	std::vector<double> container; //this will contain all the elements for the final sum


	// PART 1

	///Initialization 
	BinaryTree<const int, double> linked_list_tree;
	std::cout << "\nBENCHMARK PART 1\nlinked list tree size = "<< N1 << std::endl;
	
	std::cout << "initializing linked_list_tree . . ." << std::endl;
	for(int i = 0; i<N1; i++)
		linked_list_tree.insert(i,i);

	// building a vector of random ordered numbers
	std::vector<double> random_permutation_vector;
	for(int i = 0; i<N1; i++)
		random_permutation_vector.push_back(i);
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.end() );

	
	//timing
	std::cout << "accessing all the elements . . ." << std::endl;
	auto begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		container.push_back(linked_list_tree[e]);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "LINKED_LIST_TREE: " << total << "us, average = " << total/double(N1) << "us" << std::endl;
	



	//PART 2

	std::cout << "\nBENCHMARK PART 2\ntree size = "<< N2 << std::endl;

	// building a vector of random ordered numbers
	std::vector<double> random;
	for(int i = 0; i<N2; i++)
		random.push_back(i);
	std::random_shuffle ( random.begin(), random.end() );

	BinaryTree<const int, double> balanced_tree;
	BinaryTree<const int, double> random_tree;
	std::map<const int, double> map;

	// initializing std map
	std::cout << "initializing std::map  . . ." << std::endl;
	for(int i = 0; i<N2; i++)
		map.insert(std::make_pair(i,i));

	// initializing random tree
	std::cout << "initializing random tree . . ." << std::endl;
	for(auto e : random)
	{
		random_tree.insert(e,e);
	}

	// balancing one of the trees
	std::cout << "balancing tree . . ." << std::endl;
	balanced_tree = random_tree;
	balanced_tree.balance();



	//////////// Performance measuring ////////////

	// reshuffling for random access
	std::random_shuffle ( random.begin(), random.end());

	std::cout << "accessing all the elements . . ." << std::endl;


	//RANDOM TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random)
	{
		container.push_back(random_tree[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "RANDOM_TREE: " << total << "us, average = " << total/double(N2) << "us" << std::endl;

	//BALANCED TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random)
	{
		container.push_back(balanced_tree[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "BALANCED_TREE: " << total << "us, average = " << total/double(N2) << "us" << std::endl;

	//MAP
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random)
	{
		container.push_back(map[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "MAP: " << total << "us, average = " << total/double(N2) << "us" << std::endl;



	//perform the final sum, so we are sure that the elements were really accessed
	double s{0};
	for(double x: container)
		s+=x;

	std::cout << "sum is: " << s << std::endl;
	
    return 0;
}
