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
	const bool full_test = (arcv<3) ? true : false;
	//const size_t load_size = 2; //how many byte for each data

	BinaryTree<const int, double> linked_list_tree;
	BinaryTree<const int, double> balanced_tree;
	BinaryTree<const int, double> random_tree;
	std::map<const int, double> map;

	
	//////////// Initializing trees ////////////
	std::cout << N << ";";
	

	if(full_test)
	{
		//std::cout << "initializing linked_list_tree . . ." << std::endl;
		for(int i = 0; i<N; i++)
		{
			linked_list_tree.insert(i,i);
		}
	}


	for(int i = 0; i<N; i++)
	{
		map.insert(std::make_pair(i,i));
	}


	// building a vector of random ordered numbers
	std::vector<double> random_permutation_vector;
	for(int i = 0; i<N; i++)
		random_permutation_vector.push_back(i);
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.end() );

	
	// initializing random tree

	for(auto e : random_permutation_vector)
	{
		random_tree.insert(e,e);
	}

	// balancing one of the trees

	balanced_tree = random_tree;
	balanced_tree.balance();
	
	const BinaryTree<const int, double> &t = balanced_tree;
	balanced_tree[2] = 12;
	

	
	//////////////////////////////////////////////////////////////////////////////////////




	//////////// Performance measuring ////////////

	// reshuffling for random access
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.begin());

	// just for initializing them
	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();

	//
	std::vector<double> container;
	

	//LINKED LIST TREE
	if(full_test)
	{
		begin = std::chrono::high_resolution_clock::now();
		for(auto e : random_permutation_vector)
		{
			container.push_back(linked_list_tree[e]);
		}
		end = std::chrono::high_resolution_clock::now();
		total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
		std::cout << "LINKED_LIST_TREE: " << total/double(N) << std::endl;
	}

	//RANDOM TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		container.push_back(random_tree[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "RANDOM_TREE: " << total/double(N)<< ";";

	//BALANCED TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		container.push_back(balanced_tree[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "BALANCED_TREE: " << total/double(N) << ";";

	//MAP
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		container.push_back(map[e]);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "MAP: " << total/double(N) << ";" << std::endl;

	double s{0};
	for(double x: container)
		s+=x;

	//std::cout << s << std::endl;

	/*
	 ofstream myfile;
         myfile.open ("example.txt");
 	 myfile << "Writing this to a file.\n";
 	 myfile.close();
	*/
	
	
    return 0;
}
