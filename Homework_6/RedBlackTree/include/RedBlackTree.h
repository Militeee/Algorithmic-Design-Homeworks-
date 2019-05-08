#include "../../BinaryTree/include/BinaryTreeRec.h"

template <class K, class V, class F = std::less<K>>

class RedBlackTree: public BinaryTree<K,V,F>{
    
    struct RBnode: public BinaryTree<K,V,F>::Node<K,V,F>{
        bool red = true;

        bool is_right_child(){
            return _parent != nullptr and _parent->_right == this;
        }

        RBnode* sibling(){
            if(this->is_right_child()) return _left;
            return _right;
        }

        RBnode* uncle(){
            return this->_parent->sibling();
        }

        RBnode* get_child(bool left){
            if(left) return _left.get();
            return _right.get();
        }


        friend bool reverse_side(bool left){
            if(left) return false;
            return true;
        }

        void set_child(bool left, RBnode* y){
            if(left){ 
                _left->_left.release();
                 _left->_right.release();
                _left.reset(y);
            
            }
            else {
                _right->_left.release();
                 _right->_right.release();
                _right.reset(y);
            }
        }

        RBnode* grandparent(){ return _parent->_parent;}
    };

    void rotate(RBnode* x, bool is_left);
    void insert(const K& key, const V& value);
    void fix_insert_rbt(RBnode* z);
    RBnode* fix_insert_rbt_case1(RBnode* z);
    RBnode* fix_insert_rbt_case2(RBnode* z);
    void fix_insert_rbt_case3(RBnode* z);
    V& remove(const K& key);
    void fix_remove_rbt(RBnode* x);
    void fix_remove_rbt_case1(RBnode* x);
    RBnode* fix_remove_rbt_case2(RBnode* x);
    void fix_remove_rbt_case3(RBnode* x);
    void fix_remove_rbt_case4(RBnode* x);
};

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::rotate(RBnode* x, bool is_left){
    bool r_side <- reverse_side(is_left);
    RBnode* y <- x->get_child(r_side);
    transplant(x,y);
    RBnode* beta <- y->get_child(side);
    transplant(beta,x);
    x->set_child(r_side, beta);
    if(beta != nullptr)
        beta->_parent = x;
}

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::insert(const K& key, const V& value){
        std::pair<typename BinaryTree<K,V,F>::Iterator,bool> ret = BinaryTree<K,V,F>::insert(const K& key, const V& value);
        RedBlackTree<K,V,F>::RBnode* z = ret.first.getNode();
        fix_insert_rbt();
}

template <class K, class V, class F = std::less<K>>
RedBlackTree<K,V,F>::RBnode* RedBlackTree<K,V,F>::fix_insert_rbt_case1(RBnode* z){
    z->uncle()->red = false;
    z->_parent->red = false;
    z->grandparent()->red = red;
    return z->grandparent();
}

template <class K, class V, class F = std::less<K>>
RedBlackTree<K,V,F>::RBnode* RedBlackTree<K,V,F>::fix_insert_rbt_case2(RBnode* z){
    RBnode* p = z->_parent;
    bool z_side = !(z->is_right_child());
    rotate(p,reverse_side(z_side));
    return p;
}

template <class K, class V, class F = std::less<K>>
RedBlackTree<K,V,F>::RBnode* RedBlackTree<K,V,F>::fix_insert_rbt_case3(RBnode* z){
    RBnode* g = z->grandparent();
    z->_parent->red = false;
    g->red = true;
    rotate(g,!(z->is_right_child()));
}

template <class K, class V, class F = std::less<K>>
RedBlackTree<K,V,F>::RBnode* RedBlackTree<K,V,F>::fix_insert_rbt(RBnode* z){
    while(z->_parent != nullptr && 
        (z->grandparent() != nullptr || z->_parent->red == true)){
            if(z->uncle()->red == true){
                z = fix_insert_rbt_case1(z);
            }
            else{
                if(z->is_right_child() != z->_parent->is_right_child()){
                    z = fix_insert_rbt_case2(z->_parent);
                }
                fix_insert_rbt_case3(z);
            }
        }
    root->red = false; 
}

template <class K, class V, class F = std::less<K>>
V& RedBlackTree<K,V,F>::remove(const K& key){
    Iterator s_res = find(key);
    RBode* y = s_res.getNode();
    V& ret = BinaryTree<K,V,F>::remove(y);
    RBnode* x;
    if (y->red == false){
        if(y->_left == nullptr)
            x = y->_right;
        else
            x = y->_left;
    }
    fix_remove_rbtree(x);
    return(ret);  
}

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::fix_remove_rbt(RBnode* x){
    while(x != root && x->red == false){
        RBnode* w = x->sibling();
        if(w->red == true){
            x = fix_remove_rbt_case1(x);
        }
        else{
            int x_side = !(x->is_right_child());
            int r_side = !(x_side);
        }

        if(w->get_child(r_size)->red == true){
            fix_remove_rbt_case4(x);
            return;
        }
        else{
            if(w->get_child(x_size)->red == true){
                fix_remove_rbt_case3(x);
            }
            else{
                fix_remove_rbt_case2(x);
            }
        }
    }
}

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::fix_remove_rbt_case1(RBnode* x){
    x->sibling()->_red = false;
    x->_paremt->_red = true;
    rotate(x,!(x->is_right_child()));
}

template <class K, class V, class F = std::less<K>>
RedBlackTree<K,V,F>::RBnode* RedBlackTree<K,V,F>::fix_remove_rbt_case2(RBnode* x){
    x->sibling()->_red = true;
    return x->_parent;
}

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::fix_remove_rbt_case3(RBnode* x){
    int x_side = !(x->is_right_child());
    int r_side = !(x_side);
    x = x->get_child(r_size);
    x->get_child(x_size)->red = false;
    x->red = true;
    rotate(x,r_side);
}

template <class K, class V, class F = std::less<K>>
void RedBlackTree<K,V,F>::fix_remove_rbt_case4(RBnode* x){
    int x_side = !(x->is_right_child());
    int r_side = !(x_side);
    x = x->get_child(r_size);
    x->get_child(r_size)->red = false;
    x->red = x->_parent->red;
    x->_parent->red = false;
    rotate(x,x_side);
}

