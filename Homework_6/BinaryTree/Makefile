CXX = c++
INCLUDE = include/BinaryTreeRec.h
TEST = test/BTtests.cpp  
REMOVE = test/removeTest.cpp

all:  unitTest removeTest

unitTest: $(TEST) $(INCLUDE) 
	$(CXX) -O3 -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra

removeTest: $(REMOVE) $(INCLUDE) 
	$(CXX) -O3 -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra -ggdb

format: $(SRC) include/BinaryTree.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"


clean:
	@rm -rf *~ */*~  unitTest removeTest


.PHONY: clean all format document
