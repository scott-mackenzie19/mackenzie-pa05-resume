//
// Created by Kate Bouis on 11/13/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_F
using namespace std;
#include <iostream>

template <typename T>
class DSAvlTree{
private:
    class AvlNode {
    public:
        T element;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode(const T& theElement, AvlNode* lt, AvlNode* rt, int h = 0): element (theElement), left(lt), right (rt), height (h) {}
    };
    AvlNode* root;
    T& insertPrivate (AvlNode*&, const T&);
    bool containsPrivate (AvlNode* c, T val) {
        if (c == nullptr) return false;
        else if (c->element == val) return true;
        else if (val < c-> element) return containsPrivate (c-> left, val);
        else return containsPrivate (c-> right, val);
    }
    DSAvlTree(const DSAvlTree<T>& rhs) {}
    DSAvlTree<T>& operator=(const DSAvlTree<T>& rhs) {}
public:
    DSAvlTree(): root(nullptr) {}
    ~DSAvlTree() {makeEmpty(root);}
    void makeEmpty(AvlNode*);
    T& insert (const T& x) {return insertPrivate (root, x);}
    void balance (AvlNode*&);
    void rotateWithLeftChild (AvlNode*&);
    void rotateWithRightChild (AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void doubleWithRightChild(AvlNode*&);
    int height (AvlNode*);
    int max (int, int);
    bool contains (T val) {return containsPrivate (root, val);}
};

template <typename T>
void DSAvlTree<T>::makeEmpty(AvlNode* n) {
    if (n) {
        makeEmpty(n->left);
        makeEmpty(n->right);
        delete n;
    }
}
template <typename T>
int DSAvlTree<T>::height (AvlNode* n) {
    if (n == nullptr) return 0;
    return n->height;
}

template <typename T>
void DSAvlTree<T>::balance (AvlNode*& t) {
    if (t == nullptr) return;
    if (height (t->left) - height (t->right) > 1) {
        if (height (t->left->left) >= height (t->left->right))
            rotateWithLeftChild(t);
        else doubleWithLeftChild(t);
    } else if (height (t->right) - height (t->left) > 1) {
        if (height (t->right->right) >= height (t-> right->left))
            rotateWithRightChild(t);
        else doubleWithRightChild(t);
    }
}

template <typename T>
void DSAvlTree<T>::rotateWithLeftChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> left;
    k2-> left = k1-> right;
    k1->right = k2;
    k2->height = max (height(k2->left), height (k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
    k1->height =max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) +1;
}

template <typename T>
void DSAvlTree<T>::rotateWithRightChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> right;
    k2->right = k1 -> left;
    k1-> left = k2;
    k2 -> height = max (height(k2->right), height (k2->left)) + 1;
    k1->height = max (height(k1->right), k2->height)+1;
    k2 = k1;
    k1->height =max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) +1;
}
template <typename T>
void DSAvlTree<T>::doubleWithLeftChild(AvlNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild (k3);
}
template <typename T>
void DSAvlTree<T>::doubleWithRightChild(AvlNode*& k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild (k3);
}

template <typename T>
int DSAvlTree<T>::max (int a, int b) {
    if (a>=b) return a;
    else return b;
}

template<typename T>
T& DSAvlTree<T>::insertPrivate(AvlNode*& t, const T& x) {
    if (contains(x)) return x;
    if (t==nullptr) {
        t = new AvlNode (x, nullptr, nullptr);
        return t->element;
    }
    else if (x < t->element) {
        int& temp = insertPrivate (t->left, x);
        balance (t);
        return temp;
    }
    else if (t -> element < x) {
       int& temp= insertPrivate (t -> right, x);
       balance (t);
       return temp;
    }
    t->height = 1 + max (height (t->left), height (t-> right));
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
