#ifndef __RB_TREE__
#define __RB_TREE__
#include "../../BinaryTree/include/BinaryTreeRec.h"
// RB tree, the implementation is from the book, in fact the code on the slide
// seems to be shorter, however I started this way and decided to go on because
// it is working Actually it uses an empty black node NIL instead of a null
// pointer to simplify the algorithm , so it does not really use the old
// functions and much of the methods have been written again folowing the Comen
// Book

template<class K, class V, class F = std::less<K>>

class RedBlackTree : public BinaryTree<K, V, F>
{
public:
  class Iterator : public BinaryTree<K, V, F>::Iterator
  {};
  // function to perform the left rotation as in the slides
  void left_rotate(typename BinaryTree<K, V, F>::Node* x);
  // same but right
  void right_rotate(typename BinaryTree<K, V, F>::Node* x);
  // insert a new value recovering the RB property
  void insert(const K& key, const V& value);
  // remove a node keeping the RB property
  const V& remove(const K& key);
  // find out if a tree can be a RB tree
  bool isRBvalid(typename BinaryTree<K, V, F>::Node* node);
  // pretty printing of a tree with levels
  void printTree(typename BinaryTree<K, V, F>::Node* root);

  // custom destructor
  ~RedBlackTree()
  {
    destroy(BinaryTree<K, V, F>::root);
    delete NIL;
    BinaryTree<K, V, F>::root = nullptr;
  }

private:
  // empty black node to be used instead of a nullptr
  typename BinaryTree<K, V, F>::Node* NIL =
    new typename BinaryTree<K, V, F>::Node(false);

  // aux function for the remove
  void remove(typename BinaryTree<K, V, F>::Node* node);
  // recover the RB property after an insertion
  void fix_insert_rbt(typename BinaryTree<K, V, F>::Node* z);
  // recover the RB property after a remove
  void fix_remove_rbt(typename BinaryTree<K, V, F>::Node* x);
  // find a node with a specific key
  typename BinaryTree<K, V, F>::Node* find_node(const K& key);
  // compute the smallest value of a tree or subtree
  typename BinaryTree<K, V, F>::Node* first_node(
    typename BinaryTree<K, V, F>::Node* node);
  // calculate recursively the black height starting from a node
  int blackHeight(typename BinaryTree<K, V, F>::Node* node);
  // aux function fo the destructor
  void destroy(typename BinaryTree<K, V, F>::Node*);
};

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::left_rotate(typename BinaryTree<K, V, F>::Node* x)
{
  // get the node on my right
  typename BinaryTree<K, V, F>::Node* y = x->_right;
  // attach the "beta" to x
  x->_right = y->_left;
  // se the "beta" parent
  if (y->_left != NIL) {
    y->_left->_parent = x;
  }
  // set the new y parent
  y->_parent = x->_parent;
  // if x was the root, now I am the new root
  if (x->_parent == NIL) {
    BinaryTree<K, V, F>::root = y;
  }
  // if x right child add me on the right of is parent and vice-versa
  else {
    if (x == x->_parent->_left) {
      x->_parent->_left = y;
    } else {
      x->_parent->_right = y;
    }
  }
  // set x as a left child
  y->_left = x;
  // and obv update the parent
  x->_parent = y;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::right_rotate(typename BinaryTree<K, V, F>::Node* x)
{
  // same as before but inverted
  typename BinaryTree<K, V, F>::Node* y = x->_left;
  x->_left = y->_right;
  if (y->_right != NIL) {
    y->_right->_parent = x;
  }
  y->_parent = x->_parent;
  if (x->_parent == NIL) {
    BinaryTree<K, V, F>::root = y;
  } else if (x == x->_parent->_right) {
    x->_parent->_right = y;
  } else {
    x->_parent->_left = y;
  }
  y->_right = x;
  x->_parent = y;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::insert(const K& key, const V& value)
{
  // It is similar to the BT insert
  // but this one does not use the search function
  if (BinaryTree<K, V, F>::root == nullptr)
    BinaryTree<K, V, F>::root = NIL;
  typename BinaryTree<K, V, F>::Node* z =
    new typename BinaryTree<K, V, F>::Node(key, value, nullptr);
  typename BinaryTree<K, V, F>::Node* y = NIL;
  typename BinaryTree<K, V, F>::Node* x = BinaryTree<K, V, F>::root;
  while (x != NIL) {
    y = x;
    if (this->cmp(key, x->entry.first)) {
      x = x->_left;
    } else {
      x = x->_right;
    }
  }
  z->_parent = y;
  if (y == NIL) {
    BinaryTree<K, V, F>::root = z;
  } else if (this->cmp(key, y->entry.first)) {
    y->_left = z;
  } else {
    y->_right = z;
  }
  z->_right = NIL;
  z->_left = NIL;
  z->red = true;
  fix_insert_rbt(z);
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::fix_insert_rbt(typename BinaryTree<K, V, F>::Node* z)
{
  // fix the RB property going solving the 4 cases presented in the slides
  while (z->_parent->red) {
    if (z->_parent == z->grandparent()->_left) {
      typename BinaryTree<K, V, F>::Node* y = z->grandparent()->_right;
      if (y->red) {
        // case 1
        z->_parent->red = false;
        y->red = false;
        z->grandparent()->red = true;
        z = z->grandparent();
      } else {
        if (z == z->_parent->_right) {
          // case 2
          z = z->_parent;
          left_rotate(z);
        }
        // case 3
        z->_parent->red = false;
        z->grandparent()->red = true;
        right_rotate(z->grandparent());
      }
    } else {
      typename BinaryTree<K, V, F>::Node* y = z->grandparent()->_left;
      if (y->red) {
        // case 1
        z->_parent->red = false;
        y->red = false;
        z->grandparent()->red = true;
        z = z->grandparent();
      }

      else {
        if (z == z->_parent->_left) {
          // case 2
          z = z->_parent;
          right_rotate(z);
        }
        // case 3
        z->_parent->red = false;
        z->grandparent()->red = true;
        left_rotate(z->grandparent());
      }
    }
  }
  BinaryTree<K, V, F>::root->red = false;
}

template<class K, class V, class F>
typename BinaryTree<K, V, F>::Node*
RedBlackTree<K, V, F>::find_node(const K& key)
{
  // find a node with a given key
  typename BinaryTree<K, V, F>::Node* x = BinaryTree<K, V, F>::root;
  while (x != NIL) {
    if (this->cmp(key, x->entry.first)) {
      x = x->_left;
    } else if (!(this->cmp(key, x->entry.first)) &&
               !(this->cmp(x->entry.first, key))) {
      return x;
    } else {
      x = x->_right;
    }
  }
  return NIL;
}

template<class K, class V, class F>

const V&
RedBlackTree<K, V, F>::remove(const K& key)
{
  typename BinaryTree<K, V, F>::Node* node = find_node(key);
  const V& ret = node->entry.second;
  if (node != NIL) {
    remove(node);
  }
  return ret;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::remove(typename BinaryTree<K, V, F>::Node* node)
{
  // it's basically similar to the Binary tree remove
  // but this time I have also to take care of the colors
  typename BinaryTree<K, V, F>::Node* y;
  typename BinaryTree<K, V, F>::Node* x;
  if (node->_left == NIL || node->_right == NIL) {
    y = node;
  } else {
    y = first_node(node);
  }
  if (y->_left != NIL) {
    x = y->_left;
  } else {
    x = y->_right;
  }
  x->_parent = y->_parent;
  if (y->_parent == NIL) {
    BinaryTree<K, V, F>::root = x;
  } else {
    if (y == y->_parent->_left) {
      x->_parent->_left = x;
    } else {
      y->_parent->_right = x;
    }
  }
  if (y != node) {
    node = y;
  }
  if (!y->red)
    fix_remove_rbt(x);
  delete y;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::fix_remove_rbt(typename BinaryTree<K, V, F>::Node* x)
{
  // fix the RB property going solving the 4 cases presented in the slides
  while (x != BinaryTree<K, V, F>::root && !x->red) {
    if (x == x->_parent->_left) {
      typename BinaryTree<K, V, F>::Node* w = x->_parent->_right;

      if (w->red) {
        // case 1

        w->red = false;
        x->_parent->red = true;
        left_rotate(x->_parent);
        w = x->_parent->_right;
      }

      // case 2

      if (!w->_left->red && !w->_right->red) {
        w->red = true;
        x = x->_parent;
      } else {
        if (!w->_right->red) {
          // case 3

          w->_left->red = false;
          w->red = true;
          right_rotate(w);
          w = x->_parent->_right;
        }
        // case 4

        w->red = x->_parent->red;
        x->_parent->red = false;
        w->_right->red = false;

        left_rotate(x->_parent);
        x = BinaryTree<K, V, F>::root;
      }
    } else {
      typename BinaryTree<K, V, F>::Node* w = x->_parent->_left;
      if (w->red) {
        // case 1
        w->red = false;
        x->_parent->red = true;
        right_rotate(x->_parent);
        w = x->_parent->_left;
      }
      // case 2
      if (!w->_right->red && !w->_left->red) {
        w->red = true;
        x = x->_parent;
      } else {
        if (!w->_left->red) {
          // case 3
          w->_right->red = false;
          w->red = true;
          left_rotate(w);
          w = x->_parent->_left;
        }
        // case 4
        w->red = x->_parent->red;
        x->_parent->red = false;
        w->_left->red = false;
        right_rotate(x->_parent);
        x = BinaryTree<K, V, F>::root;
      }
    }
  }
  x->red = false;
}

template<class K, class V, class F>
int
RedBlackTree<K, V, F>::blackHeight(typename BinaryTree<K, V, F>::Node* node)
{
  // if I'm NIL means I'm a black leave
  if (node == NIL)
    return 1;
  // get the left and right heights
  int lheight = blackHeight(node->_left);
  int rheight = blackHeight(node->_right);
  // If I'm black I would contribute instead not
  int add = node->red == true ? 0 : 1;
  // if the black height is not equal return -1
  if (lheight == -1 || rheight == -1 || lheight != rheight)
    return -1;
  // else return my subtree black height
  else
    return add + lheight;
}

template<class K, class V, class F>
bool
RedBlackTree<K, V, F>::isRBvalid(typename BinaryTree<K, V, F>::Node* node)
{
  return blackHeight(BinaryTree<K, V, F>::root) != -1;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::printTree(typename BinaryTree<K, V, F>::Node* root)
{
  // function to print the levels
  if (root == NIL)
    return;

  std::queue<typename BinaryTree<K, V, F>::Node*> q;

  q.push(root);
  // use a queue to get all the node of a level
  // while is no empty
  while (q.empty() == false) {
    // number of node in a level
    int nodeCount = q.size();

    while (nodeCount > 0) {
      // print the nodes and push the children in the queue
      typename BinaryTree<K, V, F>::Node* node = q.front();
      std::cout << node->entry.first << " ";
      q.pop();
      if (node->_left != NIL)
        q.push(node->_left);
      if (node->_right != NIL)
        q.push(node->_right);
      nodeCount--;
    }
    std::cout << std::endl;
  }
}

template<class K, class V, class F>
typename BinaryTree<K, V, F>::Node*
RedBlackTree<K, V, F>::first_node(typename BinaryTree<K, V, F>::Node* node)
{
  // find the leftmost node
  while (node->_left != NIL)
    node = node->_left;
  return node;
}

template<class K, class V, class F>
void
RedBlackTree<K, V, F>::destroy(typename BinaryTree<K, V, F>::Node* node)
{
  if (node == NIL || node == nullptr)
    return;
  if (node->_right != NIL)
    destroy(node->_right);
  if (node->_left != NIL)
    destroy(node->_left);
  delete node;
}
#endif //__RB_TREE__