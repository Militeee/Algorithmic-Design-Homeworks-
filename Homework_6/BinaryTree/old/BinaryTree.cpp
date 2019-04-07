#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>

template <class K, class V, class F = std::less<K>>
class BinaryTree
{
    struct Node
    {
        std::unique_ptr<Node> _left;
        std::unique_ptr<Node> _right;
        Node* _parent;
        std::pair<const K, V> entry; 
        Node(const K& key, const V& value, Node* parent,Node* left = nullptr, Node* right = nullptr) : _left{left}, _right{right}, _parent{parent},entry{std::pair<K,V>(key,value)} {}
        ~Node() = default;
    };
    std::unique_ptr<Node> root;
    Node* first_node() const;
	Node* search (const K& key);
    F cmp;
    public:
    BinaryTree(F comparison = F{}): cmp{comparison} {}
    ~BinaryTree() = default;
    BinaryTree (const BinaryTree& bt);
    BinaryTree& operator=(const BinaryTree& bt);
    BinaryTree(BinaryTree&& bt) noexcept = default;
    BinaryTree& operator=(BinaryTree&& bt) noexcept = default;
    

    //clear the content of the tree
    void clear() {root.reset();}

    //balance the tree
    void balance();

    //**optional** implement the `value_type& operator[](const key_type& k)` function int the `const` and `non-const` versions). This functions, should return a reference to the value associated to the key `k`. If the key is not present, a new node with key `k` is allocated having the value `value_type{}`
    V& operator[](const K& key) noexcept;
    const V& operator[](const K& key) const noexcept;

    class Iterator;
    class ConstIterator;

    //return an `iterator` to the first node (which likely will not be the root node)
    Iterator begin() {Node* fn = first_node(); return Iterator{fn};}

    //return a proper `iterator`
    Iterator end() { return Iterator{nullptr}; }

    //return a `const_iterator` to the first node
    ConstIterator begin() const {Node* fn = first_node(); return ConstIterator{fn};}

    //return a proper `const_iterator`
    ConstIterator end() const { return ConstIterator{nullptr}; }

    ConstIterator cbegin() const {Node* fn = first_node(); return ConstIterator{fn};}

    ConstIterator cend() const { return ConstIterator{nullptr}; }


    //find a given key and return an iterator to that node. If the key is not found returns `end()`
    Iterator find(const K& key);
    //used to insert a new pair key-value
    std::pair<Iterator,bool> insert (const K& key, const V& value);    
    template <class k,class v, class f> 
    friend std::ostream& operator<<(std::ostream&, const BinaryTree<k,v,f>&);

    void copy_util(const BinaryTree::Node& old);

    std::vector<std::pair<const K, V>> to_list() const;
};

template <class K, class V, class F>

class BinaryTree<K,V,F>::Iterator : public std::iterator<std::forward_iterator_tag,V>
{
    using Node = BinaryTree<K,V,F>::Node;
    Node* pointed;

    public:
    Iterator(Node* node) : pointed{node} {}
    Iterator(const Iterator&) = default;
    std::pair<const K, V>& operator*() const {return pointed->entry;} 

    Iterator& operator++(); 
    Iterator operator++(int)
    {
        Iterator it{*this};
        ++(*this);
        return it;
    }
    bool operator==(const Iterator& other) {return pointed == other.pointed;}
    bool operator!=(const Iterator& other)  {return !(*this == other);}

};

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Iterator& BinaryTree<K,V,F>::Iterator::operator++()
{
    if(pointed->_right)
    {   
        pointed = pointed->_right.get();
        while(pointed->_left)
            pointed = pointed->_left.get();
        return (*this);
    }
    auto key = pointed->entry.first; 
    while(pointed != nullptr && pointed->entry.first <= key)
    {
        pointed = pointed->_parent;
    }
    return (*this);

}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Node* BinaryTree<K,V,F>::first_node() const
{
    Node* node = root.get();
    while(node->_left != nullptr)
        node = node->_left.get();
    return node;
}

template <class K, class V, class F>

class BinaryTree<K,V,F>::ConstIterator : public BinaryTree<K,V,F>::Iterator
{ 
    public:
        using non_const_it = BinaryTree<K,V,F>::Iterator;
        using non_const_it::Iterator;
        const std::pair<const K, V>& operator*() const {return non_const_it::operator*(); }

};

template <class K, class V, class F>

BinaryTree<K,V,F>::BinaryTree (const BinaryTree& bt)
{
    BinaryTree{};
    this->copy_util(*bt.root);
}

template <class K, class V, class F>
void BinaryTree<K,V,F>::copy_util(const BinaryTree::Node& old)
{
    insert(old.entry.first, old.entry.second);
    if(old._left != nullptr)
        copy_util(*old._left);
    if(old._right != nullptr)
        copy_util(*old._right);
}

template <class K, class V, class F>
BinaryTree<K,V,F>& BinaryTree<K,V,F>::operator=(const BinaryTree& bt)
{
    root.reset();
    auto tmp = bt;
    (*this) = std::move(tmp);
}

template <class K, class V,class F>
std::pair<typename BinaryTree<K,V,F>::Iterator,bool> BinaryTree<K,V,F>::insert (const K& key, const V& value)
{
	
	if(!root)
	{
		root.reset(new Node(key,value,nullptr));
		return std::pair<Iterator,bool>{Iterator{root.get()},true};
	}
	Node* node = search(key);

	if(!cmp(node->entry.first, key) && !cmp(key, node->entry.first))
		return std::pair<Iterator,bool>{Iterator{node},false};
		

	if(cmp(node->entry.first, key))
	{
		node->_right.reset(new Node(key,value,node));
		return std::pair<Iterator,bool>{Iterator{node->_right.get()},true};
	}
	else 
	{
		node->_left.reset(new Node(key,value,node));
		return std::pair<Iterator,bool>{Iterator{node->_left.get()},true};
	}
	

	
}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Node* BinaryTree<K,V,F>::search (const K& key)
{
	Node* node = root.get();
	auto k = node->entry.first;
	while(node->_left != nullptr || node->_right != nullptr)
	{
		if(!cmp(k,key) && !cmp(key,k))
			return node;

    		if(cmp(k,key))
        	{
			if(node->_right)
				node=node->_right.get();
			else return node;
        	}
	
		if(cmp(key,k))
        	{
			if(node->_left)
				node=node->_left.get();
			else return node;
        	}
		k = node->entry.first;
	}
	
	return node;
}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Iterator BinaryTree<K,V,F>::find(const K& key)
{
	if (root == nullptr) return end();
    Node* node = search(key);
	if(!cmp(node->entry.first,key) && !cmp(key,node->entry.first))
		return Iterator(node);

	else return end();
}
template <class K, class V, class F>
V& BinaryTree<K,V,F>::operator[](const K& key) noexcept 
{
    Iterator s_res = find(key);
    if(s_res != end()) return (*s_res).second;
    insert(key, V{});
    return (*find(key)).second; 
}

template <class K, class V, class F>
const V& BinaryTree<K,V,F>::operator[](const K& key) const noexcept
{
    Iterator s_res = find(key);
    if(s_res != end()) return (*s_res).second;
}


template <class k,class v, class f> 
std::ostream& operator<<(std::ostream& os, const BinaryTree<k,v,f>& bt)
{
    for(const auto& vals : bt )
        os << "(" << vals.first << ":" << vals.second << ") ";
    os << std::endl;
    return os;
}


template<class T>
std::vector<T> reorder(std::vector<T> list)
{
	std::vector<T> v{};
	if(list.size()<2)
		return list;
	
	int middle = int(list.size()/2);

	std::vector<T> left = std::vector<T>(list.begin(), list.begin() + middle);
	left = reorder(left);

	std::vector<T> right = std::vector<T>(list.begin() + middle + 1, list.end());
	right = reorder(right);

	v.push_back(list[middle]);
	for(auto e : left) v.push_back(e);
	for(auto e : right) v.push_back(e);

	return v;
}


template <class K, class V, class F>
std::vector<std::pair<const K, V>> BinaryTree<K,V,F>::to_list() const
{
	return std::vector<std::pair<const K, V>>(begin(), end());
}


template <class K, class V, class F>
void BinaryTree<K,V,F>::balance()
{
	if(root == nullptr)
        return;
    auto list = to_list();
	list = reorder(list);

	BinaryTree<K,V> bt{};
	for(auto e : list)
		bt.insert(e.first,e.second);
	
	(*this) = std::move(bt);
	
}


