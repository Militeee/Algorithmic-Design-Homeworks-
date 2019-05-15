#ifndef __RB_TREE__
#define __RB_TREE__
#include "../../BinaryTree/include/BinaryTreeRec.h"

// RB tree, the implementation is from the book, in fact the code on the slide seems to be
// shorter, however I started this way and decided to go on because it is working

template <class K, class V, class F = std::less<K>>

class RedBlackTree: public BinaryTree<K,V,F>{
    
    public: 

    class Iterator : public BinaryTree<K,V,F>::Iterator{};
    void left_rotate(typename BinaryTree<K,V,F>::Node* x);
    void right_rotate(typename BinaryTree<K,V,F>::Node* x);
    void insert( K& key,  V& value);
    V& remove( K& key);
    bool isRBvalid(typename BinaryTree<K,V,F>::Node* node);
    int blackHeight(typename BinaryTree<K,V,F>::Node* node);
    
    private:
    void remove( typename BinaryTree<K,V,F>::Node* node);
    void fix_insert_rbt(typename BinaryTree<K,V,F>::Node* z);
    void fix_remove_rbt(typename BinaryTree<K,V,F>::Node* x, typename BinaryTree<K,V,F>::Node* x_par);
};

template <class K, class V, class F>
void RedBlackTree<K,V,F>::left_rotate(typename BinaryTree<K,V,F>::Node* x){
    // get the node on my right
    typename BinaryTree<K,V,F>::Node* y = x->_right;
    // attach the "beta" to x
    x->_right = y->_left;
    // se the "beta" parent
    if(y->_left != nullptr){
        y->_left->_parent = x;
    }
    // set the new y parent
    y->_parent = x->_parent;
    // if x was the root, now I am the new root
    if(x->_parent == nullptr){
         BinaryTree<K,V,F>::root = y;
    }
    // if x right child add me on the right of is parent and vice-versa
    else if(x == x->_parent->_left){
        x->_parent->_left = y;
    }
    else{
        x->_parent->_right = y;
    }
    // set x as a left child 
    y->_left = x;
    // and obv update the parent
    x->_parent = y;
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::right_rotate(typename BinaryTree<K,V,F>::Node* x){
    // same as before but inverted
    typename BinaryTree<K,V,F>::Node* y = x->_left;
    x->_left = y->_right;
    if(y->_right != nullptr){
        y->_right->_parent = x;
    }
    y->_parent = x->_parent;
    if(x->_parent == nullptr){
         BinaryTree<K,V,F>::root = y;
    }
    else if(x == x->_parent->_right){
        x->_parent->_right = y;
    }
    else{
        x->_parent->_left = y;
    }
    y->_right = x;
    x->_parent = y;
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::insert( K& key,  V& value){

        std::pair<typename BinaryTree<K,V,F>::Iterator,bool> ret = BinaryTree<K,V,F>::insert( key, value);
        typename BinaryTree<K,V,F>::Node* z = ret.first.getNode();
        z->red = true;
        fix_insert_rbt(z);
}


template <class K, class V, class F >
void RedBlackTree<K,V,F>::fix_insert_rbt(typename BinaryTree<K,V,F>::Node* z){
    while(z->_parent != nullptr && z->_parent->red){
        if(z->_parent == z->grandparent()->_left)
        {
            typename BinaryTree<K,V,F>::Node* y = z->grandparent()->_right;
            if(y != nullptr && y->red){
                // case 1
                z->_parent->red = false;
                y->red = false;
                z->grandparent()->red = true;
                z = z->grandparent();
            }
            else{
                if(z == z->_parent->_right){
                    // case 2
                    z = z->_parent;
                    left_rotate(z);
                }
                // case 3
                z->_parent->red = false;
                z->grandparent()->red = true;
                right_rotate(z->grandparent());
            }
        }
        else{
            typename BinaryTree<K,V,F>::Node* y = z->grandparent()->_left;
            if(y != nullptr && y->red){
                // case 1
                z->_parent->red = false;
                y->red = false;
                z->grandparent()->red = true;
                z = z->grandparent();
                }
            
            else{
                if(z == z->_parent->_left){
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

template <class K, class V, class F>

V& RedBlackTree<K,V,F>::remove( K& key){
    typename BinaryTree<K,V,F>::Iterator s_res = BinaryTree<K,V,F>::find(key);
    typename BinaryTree<K,V,F>::Node* node = s_res.getNode();
    remove(node);
    return node->entry.second;
 }

template <class K, class V, class F>
void  RedBlackTree<K,V,F>::remove( typename BinaryTree<K,V,F>::Node* node ){
    typename BinaryTree<K,V,F>::Node* y = node;
    bool red_orig = y->red;
    typename BinaryTree<K,V,F>::Node* x;
    typename BinaryTree<K,V,F>::Node* x_par;

    if(node->_right == nullptr){
        x = node->_left;
        BinaryTree<K,V,F>::transplant(node, node->_left);
    }
    else if(node->_left == nullptr){
        x = node->_right;
        BinaryTree<K,V,F>::transplant(node, node->_right);

    }
    else{
        y = BinaryTree<K,V,F>::first_node(node->_right);
        red_orig = y!=nullptr ? y->red : false;
        x = y->_right;
        if(y->_parent == node){
            x = y;
        }
        if(y->_parent != node){
            BinaryTree<K,V,F>::transplant(y, y->_right);
            y->_right = node->_right;
            y->_right->_parent = y;
        }
        BinaryTree<K,V,F>::transplant(node,y);
        y->_left = node->_left;
        y->_left->_parent = y;
        y->red = node->red;

        std::cout << x <<std::endl;

       
    }
    x_par = node->_parent;

    if(!red_orig) fix_remove_rbt(x, x_par);
}

template <class K, class V, class F >
void RedBlackTree<K,V,F>::fix_remove_rbt(typename BinaryTree<K,V,F>::Node* x,
typename BinaryTree<K,V,F>::Node* x_par){

    while(x != BinaryTree<K,V,F>::root && (x == nullptr ||!x->red)){
        if(x == x_par->_left){
           typename BinaryTree<K,V,F>::Node* w = x_par->_right;
           if(w != nullptr && w->red){
               // case 1
               w->red = false;
               x_par->red = true;
               left_rotate(x_par);
               w = x_par->_right;
           }
           // case 2
           if((w->_left == nullptr || !w->_left->red) && (w->_right == nullptr|| !w->_right->red)){
               w->red = true;
               x = x_par;
           } 
           else{
               // case 3
               if(w->_right == nullptr || !w->_right->red){
                   if(w->_left != nullptr) w->_left->red = false;
                   w->red = true;
                   right_rotate(w); 
                    w = x_par->_right;
               }
               // case 4
               w->red = x_par->red;
               x_par->red=false;
               w->_right->red = false;
               left_rotate(x_par);
               x = BinaryTree<K, V, F>::root;
           } 
        }
        else{
            typename BinaryTree<K,V,F>::Node* w = x_par->_left;
            if(w != nullptr && w->red){
               // case 1
               w->red = false;
               x_par->red = true;
               right_rotate(x_par);
                w = x_par->_left;
            }
                // case 2
            if((w->_right == nullptr|| !w->_right->red) && (w->_left == nullptr|| !w->_left->red)){
               w->red = true;
                x = x_par;
           } 
            else{
                // case 3
               if(w->_left == nullptr || !w->_left->red){
                   if(w->_right != nullptr) w->_right->red = false;
                   w->red = true;
                   left_rotate(w); 
                    w = x_par->_left;
               }
               // case 4
               w->red = x_par->red;
               x_par->red=false;
               w->_left->red = false;
               right_rotate(x_par);
               x = BinaryTree<K, V, F>::root;
            }
        x->red = false;
        }
    }
}


template <class K, class V, class F>
int RedBlackTree<K,V,F>::blackHeight(typename BinaryTree<K,V,F>::Node* node)
{
    if(node == nullptr )
        return 0;
    int lheight = blackHeight(node->_left);
    int rheight = blackHeight(node->_right);
    int add = node->red == true ? 0 : 1;
    if(lheight == -1 || rheight == -1 || lheight != rheight )
        return -1;
    else return add + lheight;


}

template <class K, class V, class F>
bool RedBlackTree<K,V,F>::isRBvalid(typename BinaryTree<K,V,F>::Node* node){

        return blackHeight(BinaryTree<K, V, F>::root) != -1;
}


#endif //__RB_TREE__