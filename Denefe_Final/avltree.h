//Created by Noah Denefe
//ndenefe@smu.edu
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

template<class T>
struct TreeNode{
    template<class U> friend class AvlTree;
public:
    //default ructor creates an empty node
    TreeNode(): left(nullptr), right(nullptr){}
    //creates a node containing desired object but does not designate a left or right pointer
    TreeNode( T& val): left(nullptr), right(nullptr),data(val){}
    //creates a node containing desired object and designates a left and right pointer
    TreeNode( T& val, TreeNode* lt, TreeNode* rt): left(lt), right(rt),data(val){}
    TreeNode( TreeNode<T>& obj): left(nullptr), right(nullptr),data(obj.data){}
    ~TreeNode(){
        left=nullptr;
        right=nullptr;
    }

private:
    TreeNode* left;
    TreeNode* right;
    T data;
};

template<class T>
class AvlTree{
public:
    AvlTree();
    AvlTree( AvlTree&);
    ~AvlTree();
    void remove(TreeNode<T>*) ;
    template<class U>
    T* find( U&) ;
    bool isEmpty() ;
    void printTree() ;
    void insert( T&);
    void remove( T&);
    int tallyNodes();
     AvlTree & operator=( AvlTree&);

private:
    TreeNode<T>* root;
    int nodeTally;

    T& elementAt(TreeNode<T> *) ;
    void insert( T&, TreeNode<T> *&) ;
    template<class U>
    TreeNode<T>* find( U&, TreeNode<T>*) ;
    void makeEmpty(TreeNode<T> *) ;
    void printTree(TreeNode<T> *) ;
    void tallyNodes(TreeNode<T> *) ;
    TreeNode<T>* clone (TreeNode<T> *) ;

    //AVL
    int height(TreeNode<T>*) ;
    int max(int, int) ;
    //case1
    void rotateWithLeftChild(TreeNode<T>*&) ;
    //case4
    void rotateWithRightChild(TreeNode<T>*&) ;
    //case3
    void doubleWithLeftChild(TreeNode<T>*&) ;
    //case2
    void doubleWithRightChild(TreeNode<T>*&) ;

};
template<class T>
AvlTree<T>::AvlTree():root(nullptr){

}

template<class T>
void AvlTree<T>::printTree(TreeNode<T>* curr){
    if(curr!=nullptr){
        printTree(curr->left);
        cout<<curr->data;
        printTree(curr->right);
    }
}
template<class T>
void AvlTree<T>::printTree(){
    if(root!=nullptr){
        printTree(root);
    }

}

template<class T>
void AvlTree<T>::tallyNodes(TreeNode<T>* curr){

    if(curr!=nullptr){
        nodeTally++;
        tallyNodes(curr->left);
        tallyNodes(curr->right);
    }

}

template<class T>
int AvlTree<T>::tallyNodes(){
    nodeTally=0;
    if(root==nullptr){
        return 0;
    }else{
        tallyNodes(root);
        return nodeTally;
    }
}

//temporary solution. should find a way to copy tree and make the 2 objects independently editable
template<class T>
AvlTree<T>::AvlTree( AvlTree & obj):root(obj.root){

}
template<class T>
void AvlTree<T>::remove(TreeNode<T> *curr) {
    if(curr!=nullptr){
        if(curr->left!=nullptr){
            remove(curr->left);
        }
        if(curr->right!=nullptr){
            remove(curr->right);
        }
        delete curr;
    }
}

template<class T>
AvlTree<T>::~AvlTree(){
    TreeNode<T>* curr=root;
    remove(curr);
}

//find a specific object in the tree and return it's address
template<class T>
template<class U>
 T* AvlTree<T>::find( U &x){
    if(root!=nullptr){

        TreeNode<T>* curr=root;

        while(curr!=nullptr){
            if (curr->data==x){
                T* temp;
                temp=&curr->data;
                return temp;
            }
            else if(curr->data<x){
                curr=curr->right;
            }else if(curr->data>x){
                curr=curr->left;
            }
        }

    }
    return nullptr;

}



//private method for inserting into bst (will eventually call a method to balance tree
template<class T>
void AvlTree<T>::insert( T& x, TreeNode<T> *& curr) {
    //at root there should be a nullptr if empty.
    if(curr==nullptr){
        //create node
        TreeNode<T>* node= new TreeNode<T>(x);
        //set pointer
        curr=node;

        //if not at destination move to next node
    }else if(x > curr->data){

        insert(x,curr->right);
    }else if(x < curr->data){

        insert(x,curr->left);
    }
    if(max(height(curr->left),height(curr->right))>1){

        if(height(curr->left)>height(curr->right)){

            if(height(curr->left->left)>=height(curr->left->right))
                rotateWithLeftChild(curr);
            else
                doubleWithLeftChild(curr);
        }
        else if(height(curr->right)>height(curr->left)){


            if(height(curr->right->right)>=height(curr->right->left))
                rotateWithRightChild(curr);
            else
                doubleWithRightChild(curr);
        }
    }

}

template<class T>
void AvlTree<T>::insert( T& x){
    //calls backend method starting at root
    if(isEmpty()){
        TreeNode<T>* node= new TreeNode<T>(x);
        root=node;
    }else
        insert(x,root);

}

template<class T>
bool AvlTree<T>::isEmpty(){
    return (root==nullptr);
}

template<class T>
int AvlTree<T>::height(TreeNode<T>* node) {
    if((node==nullptr)){
        return 0;
    }
    int l=height(node->left);
    int r=height(node->right);
    if(l>r){
        return l+1;
    }
    else{
        return r+1;
    }

}

template<class T>
int AvlTree<T>::max(int l,int r) {
    return abs(l-r);
}

template<class T>
void AvlTree<T>::rotateWithLeftChild(TreeNode<T> *& alpha) {
    TreeNode<T>* node;
    node=alpha->left;
    alpha->left=node->right;
    node->right=alpha;
    alpha=node;
}

template<class T>
void AvlTree<T>::rotateWithRightChild(TreeNode<T> *& alpha) {
    TreeNode<T>* node;
    node=alpha->right;
    alpha->right=node->left;
    node->left=alpha;
    alpha=node;
}

template<class T>
void AvlTree<T>::doubleWithLeftChild(TreeNode<T> *& alpha) {
    rotateWithRightChild(alpha->left);
    rotateWithLeftChild(alpha);
}

template<class T>
void AvlTree<T>::doubleWithRightChild(TreeNode<T> *& alpha) {
    rotateWithLeftChild(alpha->right);
    rotateWithRightChild(alpha);
}

//need to figure out how to remove middle elements without breaking tree
template<class T>
void AvlTree<T>::remove( T& x){

}

//need to figure out how to copy tree without making the trees the same
template<class T>
 AvlTree<T>& AvlTree<T>::operator=( AvlTree<T>& obj){

    TreeNode<T>* curr=root;
    TreeNode<T>* ocurr=obj.root;
    return *this;
}

#endif // AVLTREE_H
