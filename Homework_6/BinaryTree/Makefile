CXX = c++
SRC = benchmark/Performance_test.cpp
INCLUDE = include/BinaryTreeRec.h
TEST = test/BTtests.cpp  
REMOVE = test/removeTest.cpp

all: bench unitTest removeTest

bench: $(SRC) $(INCLUDE)
	$(CXX) -O3 -o $@ $^ -Iinclude -Wall -Wextra

unitTest: $(TEST) $(INCLUDE) 
	$(CXX) -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra

removeTest: $(REMOVE) $(INCLUDE) 
	$(CXX) -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra -ggdb
format: $(SRC) include/BinaryTree.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

document: 
	@doxygen documentation/Doxyfile

clean:
	@rm -rf *~ */*~ bench unitTest documentation/html


.PHONY: clean all format document
