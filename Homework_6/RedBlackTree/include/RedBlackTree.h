#ifndef __RB_TREE__
#define __RB_TREE__
#include "../../BinaryTree/include/BinaryTreeRec.h"

template <class K, class V, class F = std::less<K>>


class RedBlackTree: public BinaryTree<K,V,F>{
    
    public: 




    class Iterator : public BinaryTree<K,V,F>::Iterator{};
    
    void rotate(typename BinaryTree<K,V,F>::Node* x, bool is_left);
    void insert(const K& key, const V& value);
    void fix_insert_rbt(typename BinaryTree<K,V,F>::Node* z);
    
    const V& remove(const K& key);
    void fix_remove_rbt(typename BinaryTree<K,V,F>::Node* x);

    bool isRBvalid(typename BinaryTree<K,V,F>::Node* node);
    int blackHeight(typename BinaryTree<K,V,F>::Node* node);
    
    private:
    void fix_remove_rbt_case1(typename BinaryTree<K,V,F>::Node* x);
    typename BinaryTree<K,V,F>::Node* fix_remove_rbt_case2(typename BinaryTree<K,V,F>::Node* x);
    void fix_remove_rbt_case3(typename BinaryTree<K,V,F>::Node* x);
    void fix_remove_rbt_case4(typename BinaryTree<K,V,F>::Node* x);
    typename BinaryTree<K,V,F>::Node* fix_insert_rbt_case1(typename BinaryTree<K,V,F>::Node* z);
    typename BinaryTree<K,V,F>::Node* fix_insert_rbt_case2(typename BinaryTree<K,V,F>::Node* z);
    void fix_insert_rbt_case3(typename BinaryTree<K,V,F>::Node* z);


};

template <class K, class V, class F>
void RedBlackTree<K,V,F>::rotate(typename BinaryTree<K,V,F>::Node* x, bool is_left){
    bool r_side = reverse_side(is_left);


    typename BinaryTree<K,V,F>::Node* y = x->get_child(r_side);
    
      
   this->transplant(x,y);

    
    


    typename BinaryTree<K,V,F>::Node* beta = y->get_child(is_left);

    



    if(beta == nullptr)
        y->set_child(is_left, x);

    else this->transplant(beta,x);
        x->set_child(r_side, beta);

    //std::cout << "Ciao" << std::endl;
    //std::cout << y->_right   << std::endl;
    //std::cout << x  << std::endl;
    
    //this->printTree(this->root_get());

    //y->set_child(r_side, x);


    if(beta != nullptr)
        beta->_parent = x;
   // std::cout << x << "\t"<< x->_parent <<std::endl;
    //std::cout << x->_right << "\t"<< x->_left <<std::endl;
    //std::cout << y << "\t"<< y->_parent <<std::endl;
    //std::cout << BinaryTree<K, V, F>::root <<std::endl;


}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::insert(const K& key, const V& value){

        std::pair<typename BinaryTree<K,V,F>::Iterator,bool> ret = BinaryTree<K,V,F>::insert( key, value);
        //this->printTree(this->root_get());

        typename BinaryTree<K,V,F>::Node* z = ret.first.getNode();
        //std::cout << this->root_get()->entry.first << std::endl;
        //this->printTree(this->root_get());

        fix_insert_rbt(z);
}

template <class K, class V, class F >
typename BinaryTree<K,V,F>::Node* RedBlackTree<K,V,F>::fix_insert_rbt_case1(typename BinaryTree<K,V,F>::Node* z){
    z->uncle()->red = false;
    z->_parent->red = false;
    z->grandparent()->red = true;
    return z->grandparent();
}

template <class K, class V, class F >
typename BinaryTree<K,V,F>::Node* RedBlackTree<K,V,F>::fix_insert_rbt_case2(typename BinaryTree<K,V,F>::Node* z){


    typename BinaryTree<K,V,F>::Node* p = z->_parent;
    bool z_side = !(z->is_right_child());
    rotate(p,reverse_side(z_side));
    return p;
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::fix_insert_rbt_case3(typename BinaryTree<K,V,F>::Node* z){
                    
    typename BinaryTree<K,V,F>::Node* g = z->grandparent();
    z->_parent->red = false;
    g->red = true;
    rotate(g,z->is_right_child());
}

template <class K, class V, class F >
void RedBlackTree<K,V,F>::fix_insert_rbt(typename BinaryTree<K,V,F>::Node* z){
    while(z->_parent != nullptr && 
        (z->grandparent() != nullptr || z->_parent->red == true)){
            if(z->uncle() != nullptr && z->uncle()->red == true){
                z = fix_insert_rbt_case1(z);
            }
            else{
                if(z->is_right_child() != z->_parent->is_right_child()){

                    z = fix_insert_rbt_case2(z);

                }

                fix_insert_rbt_case3(z);

            }
        }
    BinaryTree<K,V,F>::root->red = false; 
}

template <class K, class V, class F>
const V& RedBlackTree<K,V,F>::remove(const K& key){
    typename BinaryTree<K,V,F>::Iterator s_res = BinaryTree<K, V, F>::find(key);
    typename BinaryTree<K,V,F>::Node* y = s_res.getNode();
    const V& ret = BinaryTree<K,V,F>::remove(key);
    typename BinaryTree<K,V,F>::Node* x;
    if (y->red == false){
        if(y->_left == nullptr)
            x = y->_right;
        else
            x = y->_left;
    }
    //fix_remove_rbt(x);
    return(ret);  
}

template <class K, class V, class F >
void RedBlackTree<K,V,F>::fix_remove_rbt(typename BinaryTree<K,V,F>::Node* x){
    std::cout << x << std::endl;

    while(x != BinaryTree<K,V,F>::root && x->red == false){
        typename BinaryTree<K,V,F>::Node* w = x->sibling();

        if(w != nullptr && w->red == true){
            std::cout << "caso1" << std::endl;
            fix_remove_rbt_case1(x);
        }

        int x_side = !(x->is_right_child());

        int r_side = !(x_side);


        if(w == nullptr) break;
        if( w->get_child(r_side) != nullptr && w->get_child(r_side)->red == true){
            
            std::cout << "caso4" << std::endl;

            fix_remove_rbt_case4(x);
            return;
        }
        else{
            if( w->get_child(x_side) != nullptr && w->get_child(x_side)->red == true){
                
                std::cout << "caso3" << std::endl;
                fix_remove_rbt_case3(x);
            }
            else{

                std::cout << "caso2" << std::endl;
                fix_remove_rbt_case2(x);
            }
        }
    }
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::fix_remove_rbt_case1(typename BinaryTree<K,V,F>::Node* x){
    x->sibling()->red = false;
    x->_parent->red = true;
    rotate(x,!(x->is_right_child()));
}

template <class K, class V, class F>
typename BinaryTree<K,V,F>::Node* RedBlackTree<K,V,F>::fix_remove_rbt_case2(typename BinaryTree<K,V,F>::Node* x){
    x->sibling()->red = true;
    return x->_parent;
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::fix_remove_rbt_case3(typename BinaryTree<K,V,F>::Node* x){
    int x_side = !(x->is_right_child());
    int r_side = !(x_side);
    x = x->get_child(r_side);
    x->get_child(x_side)->red = false;
    x->red = true;
    rotate(x,r_side);
}

template <class K, class V, class F>
void RedBlackTree<K,V,F>::fix_remove_rbt_case4(typename BinaryTree<K,V,F>::Node* x){
    int x_side = !(x->is_right_child());
    int r_side = !(x_side);
    x = x->get_child(r_side);
    x->get_child(r_side)->red = false;
    x->red = x->_parent->red;
    x->_parent->red = false;
    rotate(x,x_side);
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