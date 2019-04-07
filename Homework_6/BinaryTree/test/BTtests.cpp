#define __TESTBTFUN__
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include <string>
#include "BinaryTreeRec.h"
#include "TestFunction.h"
#include "catch.hpp"


typedef std::pair<const int, std::string> pair_is;
typedef std::pair<const std::string, double> pair_sd;

TEST_CASE("Testing methos of class BT", "[BinaryTree]")
{
	// initialize the trees which is also a test of the custom constructor and insert method
	BinaryTree<int,std::string> bt{};
	BinaryTree<std::string,double> bt2{};
	std::vector<int> keys{0,1,2,3,4,5,6,7,8,9};
    std::random_shuffle(keys.begin(),keys.end());
    std::vector<std::string> values{"a","b","c","d","e","f","g","h","i","l"};
	for (int i = 0; i < 10; ++i)
	{
		bt.insert(keys[i], values[keys[i]]);
		bt2.insert(std::pair<const std::string, double>{values[keys[i]], keys[i] + 0.1 });
	}
	SECTION("Testing clear and find method")
	{
		pair_is p1{0, "a"};
		pair_sd p2{"a", 0.1};
		//testing the find
		REQUIRE(*bt.find(0) == p1);
		REQUIRE(*bt2.find("a") == p2);
		// testing the clear
		bt.clear();
		bt2.clear();
		REQUIRE(bt.find(1) == bt.end());
		REQUIRE(bt2.find("a") == bt2.end());
	}

	SECTION("Testing copy constructor")
	{
		pair_is p1{0, "a"};
		pair_sd p2{"a", 0.1};
		//copy constructor
		BinaryTree<int,std::string> bt3{bt};
		BinaryTree<std::string,double> bt4{bt2};
		// testing that the two objects are identical 
		REQUIRE(*bt.find(1) == *bt3.find(1));
		REQUIRE(*bt2.find("a") == *bt4.find("a"));
		// testing that the objects are not reference to each other
		CHECK(&(*bt.find(1)) != &(*bt3.find(1)));
		CHECK(&(*bt2.find("a")) != &(*bt4.find("a")));
		bt.clear();
		bt2.clear();
		// testing that the clear doesn't affect the copy
		REQUIRE(*bt3.find(0) == p1 );
		REQUIRE(*bt4.find("a") == p2);
	}
	SECTION("Test move constructor and copy assignment")
	{
		pair_is p1(1,"b");
		pair_sd p2("b",1.1);
		BinaryTree<int,std::string> bt_copy;
		BinaryTree<std::string,double> bt2_copy;
		// copy assignement
		bt_copy = bt;
		bt2_copy = bt2;
		// testing that the copy are identical
		REQUIRE(*bt_copy.find(1) == p1);
		REQUIRE(*bt2_copy.find("b") == p2);
		// testing that the objects are not reference to each other
		CHECK(&(*bt.find(1)) != &(*bt_copy.find(1)));
		CHECK(&(*bt2.find("b")) != &(*bt2_copy.find("b")));
		// move constructor
		BinaryTree<int,std::string> bt3 = std::move(bt);
		BinaryTree<std::string,double> bt4 = std::move(bt2);
		// testing the moved structures
		REQUIRE(*bt3.find(2) == *bt_copy.find(2));
		REQUIRE(*bt4.find("b") == *bt2_copy.find("b"));

	}
	SECTION("Test move assignement")
	{
		pair_is p1(1,"b");
		pair_sd p2("b",1.1);
		// move assignement
		BinaryTree<int,std::string> bt_move;
		BinaryTree<std::string,double> bt2_move;
		bt_move = std::move(bt);
		bt2_move = std::move(bt2);
		//Testing the moved structures
		REQUIRE(*bt_move.find(1) == p1);
		REQUIRE(*bt2_move.find("b") == p2);
	}
	SECTION("Test [] operators (const and not)")
	{
		//test the returned vale when the key is in the BT
		REQUIRE(bt[2] == "c");
		REQUIRE(bt2["c"] == 2.1);
		// test the returned value when the key is not in the BT
		REQUIRE(bt[12] == std::string{});
		REQUIRE(bt2["baobab"] == 0.0);
		REQUIRE(*bt.find(12) == (std::pair<const int, std::string>{12,std::string{}}));
		REQUIRE(*bt2.find("baobab") == (std::pair<const std::string, double>{"baobab",0.0}));
		//test the same for the const method
		const std::string try1 = bt[2];
		const double try2 = bt2["c"];
		REQUIRE(try1 == "c");
		REQUIRE(try2 == 2.1);
	}
	SECTION("Test the iterators")
	{
		pair_is p1{0, "a"};
		pair_sd p2{"a", 0.1};
		pair_is p3{1, "b"};
		pair_sd p4{"b", 1.1};
		//testing end() and begin()
		REQUIRE(*bt.begin() == p1);
		REQUIRE(*bt2.begin() == p2);
		REQUIRE(bt.end() == (BinaryTree< int, std::string>::Iterator{nullptr}));
		REQUIRE(bt2.end() == (BinaryTree< std::string, double>::Iterator{nullptr}));
		
		//testing ++() and ++(int) operator
		REQUIRE(*(++(bt.begin())) == p3);
		REQUIRE(*(++(bt2.begin())) == p4);
		REQUIRE(*((bt.begin())++) == p1);
		REQUIRE(*((bt2.begin())++) == p2);
		BinaryTree<int,std::string>::Iterator it1 = bt.begin();
		BinaryTree<std::string,double>::Iterator it2 = bt2.begin();
		it1++;
		it2++;
		REQUIRE(*it1 == p3);
		REQUIRE(*it2 == p4);

		//the same for const iterators 
		REQUIRE(*bt.cbegin() == p1);
		REQUIRE(*bt2.cbegin() == p2);
		REQUIRE(bt.cend() == (BinaryTree<int, std::string>::ConstIterator{nullptr}));
		REQUIRE(bt2.cend() == (BinaryTree<std::string, double>::ConstIterator{nullptr}));
		REQUIRE(*(++(bt.cbegin())) == p3);
		REQUIRE(*(++(bt2.cbegin())) == p4);
		REQUIRE(*((bt.cbegin())++) == p1);
		REQUIRE(*((bt2.cbegin())++) == p2);
		BinaryTree<int,std::string>::ConstIterator it3 = bt.cbegin();
		BinaryTree<std::string,double>::ConstIterator it4 = bt2.cbegin();
		it3++;
		it4++;
		REQUIRE(*it3 == p3);
		REQUIRE(*it4 == p4);
	}
	SECTION("Test balance method")
	{
		bt.balance();
		bt2.balance();
		REQUIRE(bt.isBalanced(bt.root_get()) == true);
		REQUIRE(bt2.isBalanced(bt2.root_get()) == true);
	}
	SECTION("Test insert method with duplicated key")
	{
		auto resul = bt.insert(0,"castoro");
		if (!resul.second)
					(*resul.first).second = "castoro";
		REQUIRE(bt[0] == "castoro");
		auto resul2 = bt2.insert("b",3.14);
		if (!resul2.second)
					(*resul2.first).second = 3.14;
		REQUIRE(bt2["b"] == 3.14);
	}
	SECTION("Test the custom comparison function")
	{
		
		//initialize the tree
		BinaryTree<int,std::string,std::greater<int>> bt_fun{};
		for (int i = 0; i < 10; ++i)
		{
			bt_fun.insert(keys[i], values[keys[i]]);
		}
		pair_is pFirst{9, "l"};
		pair_is pSecond{8, "i"};
		//find if the tree is correctly reversed
		REQUIRE(*bt_fun.begin() == pFirst);
		REQUIRE(*(++bt_fun.begin()) == pSecond);
	}
	SECTION("Test the remove function")
	{
		bt.remove(0);
		bt2.remove("a");
		REQUIRE(bt.find(0) == bt.end());
		REQUIRE(bt2.find("a") == bt2.end());
	}
}
