#include "BinaryTreeRec.h"
#include <iostream>
#include <string>
#include <vector>

int
main()
{
  BinaryTree<int, std::string> bt{};
  std::vector<int> keys{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::random_shuffle(keys.begin(), keys.end());
  std::vector<std::string> values{ "a", "b", "c", "d", "e",
                                   "f", "g", "h", "i", "l" };
  for (int i = 0; i < 10; ++i) {
    bt.insert(keys[i], values[keys[i]]);
  }
  std::cout << bt << std::endl;
  bt.remove(std::rand() % 10);
  std::cout << bt << std::endl;

  return 0;
}