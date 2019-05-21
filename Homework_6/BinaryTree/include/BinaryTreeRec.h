/**
 * @file BinaryTreeRec.cpp
 * @author Salvatore Milite and Davide Scassola
 * @brief Advanced Programming and Scientific Computing final c++ project
 * @version 0.1
 * @date 2019-01-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef __BT_TREE__
#define __BT_TREE__

#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

bool
reverse_side(bool left)
{
  return !left;
}

/**
 * @brief Class that implements a binary tree
 *
 * The implementation is a simple not autobalancing Binary tree, it is
 * constructed with a constant templated key, a templated value and a templated
 * comparing function (the default is the < operator of the key type). It has a
 * pointer to the root node.
 *
 * @tparam K the key type
 * @tparam V the value stored in the node
 * @tparam std::less<K> the comparing function(defaul <)
 */
template<class K, class V, class F = std::less<K>>
class BinaryTree
{
protected:
  /**
   * A structure that represent the node of the tree
   * A private container that takes the  pointers to the left and right child, a
   * pointer to the parent and the entry, a pair with key and value, also hold
   * the color for the RBtree implementation.
   */
  struct Node

  {
    /** left child */
    Node* _left;
    /** right child */
    Node* _right;
    /** parent node */
    Node* _parent;
    /** color for RBtree*/
    /** pair with key and value */
    std::pair<const K, V> entry;
    /** construct a new Node object */
    bool red;

    Node(const K& key,
         const V& value,
         Node* parent,
         Node* left = nullptr,
         Node* right = nullptr,
         bool _red = true)
      : _left{ left }
      , _right{ right }
      , _parent{ parent }
      , entry{ std::pair<const K, V>{ key, value } }
      , red{ _red }
    {}
    /** default destructor */
    ~Node() noexcept = default;
    Node() = default;
    Node(bool _red)
      : Node()
    {
      red = _red;
    }

    Node* grandparent() { return _parent->_parent; }
  };
  /** Pointer to the root */
  Node* root = nullptr;

  /** The comparison operator, a functional object that returns a boolean */
  F cmp = F{};

  /**
   * @brief A function to calculate the first node (following the key order)
   * @return Node* a pointer to the first node
   */
  Node* first_node(Node* node = nullptr) const;

  /**
      auxiliary recursive function that implements the search algorithm used in
     insert and find functions
  */
  Node* search(const K& key);

  /**
   * @brief auxiliary recursive function that implements the balancing algorithm
   * used in the balance() function
   *
   *
   * Given a list of pair (key,value), this function insert in the tree the
   * elements of the list from a given begin index to a given end index, in an
   * order such that the tree will be perfectly balanced.
   *
   * @tparam std::vector<std::pair<const K, V>>& reference to the list
   * @tparam int begin index
   * @tparam int end index
   *
   */
  void balance(std::vector<std::pair<const K, V>>& list, int begin, int end);
  /**
   * @brief An utility for the copy constructor
   * It starts a recursive copy of a BT starting from a given node(ideally the
   * root). It simply insert the nodes in the caller object in the same order it
   * finds them in the tree with root = old.
   * @param old the node from which to start the copy. If is root then it copy
   * an entire tree, else just a subtree
   */
  void copy_util(const BinaryTree::Node& old, Node*& copied);
  void transplant(BinaryTree::Node* x, BinaryTree::Node* y);
  void remove(Node* node);

  // function used for the destructor, destroy iteratively the nodes
  void destroy(Node* node)
  {
    if (node == nullptr)
      return;
    if (node->_right != nullptr)
      destroy(node->_right);
    if (node->_left != nullptr)
      destroy(node->_left);
    delete node;
  }

public:
  /**
   * @brief Construct a new Binary Tree object
   */
  BinaryTree() = default;
  /**
   * @brief Destroy the Binary Tree object
   *
   */
  ~BinaryTree() { destroy(root); }
  /**
   * @brief Creates a deep copy of a binary tree
   *
   * @param bt the tree to be copied
   */

  BinaryTree(const BinaryTree& bt)
  {
    if (bt.root != nullptr)
      this->copy_util(*bt.root, this->root);
  }
  /**
   * @brief Copy assignement
   *
   * @param bt the tree to be copied
   * @return BinaryTree&
   */
  BinaryTree& operator=(const BinaryTree& bt);
  BinaryTree(BinaryTree&& bt) noexcept
    : root{ nullptr }
  {
    std::swap(root, bt.root);
  }
  // move assignement, a simpe root swap
  BinaryTree& operator=(BinaryTree&& bt) noexcept
  {
    std::swap(root, bt.root);
    return *this;
  }

  /**
   * @brief Finds out if the tree is balanced
   *
   * It compares recursively the hegihts of all the branches, and if the
   * difference in height is <= 1, it returns true
   * @param node the starting node, usually the root
   * @return true if the tree is balanced
   * @return false if the tree is not balanced
   */
  bool isBalanced(Node* node);
  /**
   * @brief Returns the height of a tree or subtree starting by a specific node
   *
   * @param node the node from where to stard
   * @return int the height
   */
  int height(Node* node);
  /**
   * @brief A getter method for the root node
   *
   * @return Node* a pointer to the root node
   */
  Node* root_get() { return root; };

  // clear the content of the tree
  void clear()
  {
    destroy(root);
    root = nullptr;
  }

  /**
   * @brief function that balance the tree
   *
   *
   * Calling this function the tree will be balanced. The underlying algorithm
   * consists in extracting the list of al pairs (key,value) of the current
   * tree, clearing the current tree, and then inserting all the pairs in such
   * an order that the tree will balanced.
   *
   */
  void balance();

  /**
   * @brief operator that return the value corresponding to a given key
   *
   *
   * If the given key corresponds to an element in the tree this operator will
   * return the value corresponding to that element. If not present, a new pair
   * with the given key and a default value will be inserted in the tree, and
   * the a reference to this new value will be returned.
   *
   * @tparam const const K& the key of the searched value
   * @return const V& reference to the value
   */
  const V& operator[](const K& key);

  /**
   * @brief operator that return the value corresponding to a given key
   *
   *
   * The functioning of this operator is analogous to the non const one, but
   * this time if an element corresponding to the given key is not found, then
   * an exception will be thrown. In this way the tree will be surely
   * unmodified.
   * @throws runtime_errors
   * @tparam const const K& the key of the searched value
   * @return const const V& reference to the value
   */
  const V& operator[](const K& key) const;

  class Iterator;
  class ConstIterator;

  /**
   * @brief a function that return an Iterator to the first element
   *
   *
   * This function returns the iterator to the first element, in the sense that
   * it correspond to the element for wich the key is the minimum between the
   * all the keys according to the tree comparing function
   *
   * @return Iterator iterator to the first element
   */
  Iterator begin()
  {
    Node* fn = first_node();
    return Iterator{ fn };
  }

  /**
   * @brief A function that return an Iterator to one past the last node
   *
   *
   * This function returns an iterator initialized with nullptr that represents
   * the end of the BinaryTree
   *
   * @return Iterator iterator to the end
   */
  Iterator end() { return Iterator{ nullptr }; }

  /**
   * @brief A constant iterator version of begin()
   *
   * @return ConstIterator constant iterator to the first node
   */
  ConstIterator begin() const
  {
    Node* fn = first_node();
    return ConstIterator{ fn };
  }

  /**
   * @brief A constant interator version of end()
   *
   * @return ConstIterator returns a constant iterator to the end of the Data
   * Structure
   */
  ConstIterator end() const { return ConstIterator{ nullptr }; }

  /**
   * @brief Same as ConstIterator begin() but explicit
   *
   * @return ConstIterator constant iterator to the first node
   */
  ConstIterator cbegin() const
  {
    Node* fn = first_node();
    return ConstIterator{ fn };
  }

  /**
   * @brief Same as ConstIterator end() but explicit
   *
   * @return ConstIterator constant iterator to the end of the Data Structure
   */
  ConstIterator cend() const { return ConstIterator{ nullptr }; }

  /**
   * @brief Finds a value with a given key and returns an iterator to it
   * @param key the key of the node to be searched
   * @return Iterator an Iterator to the node with the key or to end() if its
   * not present
   */
  Iterator find(const K& key)
  {
    Iterator it = Iterator(search(key));
    if (it != end() && it.getNode()->entry.first != key)
      it = end();
    return it;
  }
  /**
   * @brief Insert a new node with given key and value
   * It returns a std::pair with an iterator to the node and a bool. If the key
   * is not present, the new node is effectively added and the bool as value
   * true. In case the key was already in the tree the bool has value false, and
   * the user has to change the node value manually from the iterator.
   * @param key the key of the new node
   * @param value the value of the new node
   * @return std::pair<Iterator,bool> a pair with an iterator to the inserted
   * (or where the key is already present) node and a bool that indicates if the
   * new has been added
   */
  std::pair<Iterator, bool> insert(const K& key, const V& value);
  /**
   * @brief An insert which takes directly an std::pair with the right types
   *
   * @param p the std::pair to be added in the new node
   * @return std::pair<Iterator,bool> saame as the other insert()
   */
  std::pair<Iterator, bool> insert(std::pair<const K&, const V&> p)
  {
    return insert(p.first, p.second);
  }

  // remove an element, conserving the BTree properties
  const V& remove(const K& key);

  template<class k, class v, class f>
  /**
   * @brief Overloading of the operator<< for printing and writing on files
   *
   * @return std::ostream&
   */
  friend std::ostream& operator<<(std::ostream&, const BinaryTree<k, v, f>&);
};

template<class K, class V, class F>
class BinaryTree<K, V, F>::Iterator
  : public std::iterator<std::forward_iterator_tag, V>
{
  using Node = BinaryTree<K, V, F>::Node;
  Node* pointed;
  F cmp = F{};

public:
  Iterator(Node* node)
    : pointed{ node }
  {}
  Iterator(const Iterator&) = default;
  std::pair<const K, V>& operator*() const { return pointed->entry; }

  Iterator& operator++();
  Iterator operator++(int)
  {
    Iterator it{ *this };
    ++(*this);
    return it;
  }
  bool operator==(const Iterator& other) { return pointed == other.pointed; }
  bool operator!=(const Iterator& other) { return !(*this == other); }
  Node* getNode() { return pointed; };
};

template<class K, class V, class F>
typename BinaryTree<K, V, F>::Iterator&
BinaryTree<K, V, F>::Iterator::operator++()
{
  if (pointed->_right) {
    pointed = pointed->_right;
    while (pointed->_left)
      pointed = pointed->_left;
    return (*this);
  }
  auto key = pointed->entry.first;
  while (pointed != nullptr && !cmp(key, pointed->entry.first)) {
    pointed = pointed->_parent;
  }
  return (*this);
}

template<class K, class V, class F>
typename BinaryTree<K, V, F>::Node*
BinaryTree<K, V, F>::first_node(typename BinaryTree<K, V, F>::Node* node) const
{
  if (node == nullptr)
    node = root;
  // find the leftmost node
  while (node->_left != nullptr)
    node = node->_left;
  return node;
}

template<class K, class V, class F>
class BinaryTree<K, V, F>::ConstIterator : public BinaryTree<K, V, F>::Iterator
{
public:
  using non_const_it = BinaryTree<K, V, F>::Iterator;
  using non_const_it::Iterator;
  const std::pair<const K, V>& operator*() const
  {
    return non_const_it::operator*();
  }
};

template<class K, class V, class F>
void
BinaryTree<K, V, F>::copy_util(const BinaryTree::Node& old, Node*& copied)
{
  // copy recursively from a node
  copied = new Node(old.entry.first, old.entry.second, old._parent);
  if (old._left != nullptr)
    copy_util(*old._left, copied->_left);
  if (old._right != nullptr)
    copy_util(*old._right, copied->_right);
}

template<class K, class V, class F>
BinaryTree<K, V, F>&
BinaryTree<K, V, F>::operator=(const BinaryTree& bt)
{
  root = nullptr;
  auto tmp = bt;
  (*this) = std::move(tmp);
  return *this;
}

template<class K, class V, class F>
std::pair<typename BinaryTree<K, V, F>::Iterator, bool>
BinaryTree<K, V, F>::insert(const K& key, const V& value)
{
  // if I'm the first node to be inserted
  if (root == nullptr) {
    root = new Node(key, value, nullptr);
    return std::pair<Iterator, bool>{ Iterator{ root }, true };
  }
  Node* node = search(key);

  // If I'm a new node with the same key of an existing one
  if (!cmp(node->entry.first, key) && !cmp(key, node->entry.first))
    return std::pair<Iterator, bool>{ Iterator{ node }, false };

  // if I'm bigger than my parent
  if (cmp(node->entry.first, key)) {
    node->_right = new Node(key, value, node);
    return std::pair<Iterator, bool>{ Iterator{ node->_right }, true };
  }
  // If I'm smaller
  else {
    node->_left = new Node(key, value, node);
    return std::pair<Iterator, bool>{ Iterator{ node->_left }, true };
  }
}

template<class K, class V, class F>
typename BinaryTree<K, V, F>::Node*
BinaryTree<K, V, F>::search(const K& key)
{
  Node* node = root;
  if (node == nullptr)
    return nullptr;
  auto k = node->entry.first;
  // search iteratively till I find the right node or the node where to
  // insert it
  while (node->_left != nullptr || node->_right != nullptr) {
    if (!cmp(k, key) && !cmp(key, k))
      return node;

    if (cmp(k, key)) {
      if (node->_right)
        node = node->_right;
      else
        return node;
    }

    if (cmp(key, k)) {
      if (node->_left)
        node = node->_left;
      else
        return node;
    }
    k = node->entry.first;
  }

  return node;
}

template<class K, class V, class F>
const V& BinaryTree<K, V, F>::operator[](const K& key)
{
  Iterator s_res = find(key);
  if (s_res != end())
    return (*s_res).second;
  return (*insert(key, V{}).first).second;
}

template<class K, class V, class F>
const V& BinaryTree<K, V, F>::operator[](const K& key) const
{
  Iterator s_res = find(key);
  if (s_res != end())
    return (*s_res).second;
  // is a constant method, if it does not find the key it throws an exception
  throw std::runtime_error("You are trying to acces a non existing key");
}

template<class k, class v, class f>
std::ostream&
operator<<(std::ostream& os, const BinaryTree<k, v, f>& bt)
{
  for (const auto& vals : bt)
    os << "(" << vals.first << ":" << vals.second << ") ";
  os << std::endl;
  return os;
}

template<class K, class V, class F>
void
BinaryTree<K, V, F>::balance()
{
  if (root == nullptr)
    return;
  std::vector<std::pair<const K, V>> list(begin(), end());
  // free some space
  clear();
  balance(list, 0, int(list.size()) - 1);
}

template<class K, class V, class F>
void
BinaryTree<K, V, F>::balance(std::vector<std::pair<const K, V>>& list,
                             int begin,
                             int end)
{
  if (begin > end)
    return;
  int middle = begin + (end - begin) / 2;
  // int middle = (begin + end)/2;
  insert(list[middle].first, list[middle].second);
  // halve the list and do the same till the end
  balance(list, begin, middle - 1);
  balance(list, middle + 1, end);
}

template<class K, class V, class F>
void
BinaryTree<K, V, F>::transplant(BinaryTree::Node* x, BinaryTree::Node* y)
{
  // if x is root, swap y with it
  if (x->_parent == nullptr) {
    this->root = y;
  }

  else {
    // if x is right child change his parent right pointer and vice-versa
    if (x->_parent->_right == x) {
      x->_parent->_right = y;
    } else {
      x->_parent->_left = y;
    }
  }
  // if I'm not transplanting a nullpointer update the parents
  if (y != nullptr)
    y->_parent = x->_parent;
}

template<class K, class V, class F>
void
BinaryTree<K, V, F>::remove(BinaryTree::Node* node)
{
  // if no right child, transplant me with my left child and vice-versa
  if (node->_right == nullptr) {
    transplant(node, node->_left);
  } else if (node->_left == nullptr) {
    transplant(node, node->_right);
  } else { // if I have both children, find my successor
    Node* y = first_node(node->_right);
    // if my successor is not my child
    if (y->_parent != node) {
      // substitute y with is right child
      transplant(y, y->_right);
      // set right parency  for the insertion of y in place of node
      y->_right = node->_right;
      y->_right->_parent = y;
    }
    // insert the successor in place of node
    transplant(node, y);
    // set also the parency of  left part
    y->_left = node->_left;
    y->_left->_parent = y;
  }
  delete node;
}

template<class K, class V, class F>
const V&
BinaryTree<K, V, F>::remove(const K& key)
{
  Iterator s_res = find(key);
  Node* node = s_res.getNode();
  V& res = node->entry.second;
  remove(node);
  return res;
}

template<class K, class V, class F>
int
BinaryTree<K, V, F>::height(Node* node)
{
  // if I am a leaf returrn zero, or 1+the branch height
  return (node == nullptr)
           ? 0
           : 1 + std::max(height(node->_left), height(node->_right));
}

template<class K, class V, class F>
bool
BinaryTree<K, V, F>::isBalanced(Node* node)
{
  // the tree is balanced if
  return (node == NULL) ||
         (isBalanced(node->_left) && isBalanced(node->_right) &&
          std::abs(height(node->_left) - height(node->_right)) <= 1);
}

#endif //__BT_TREE__//