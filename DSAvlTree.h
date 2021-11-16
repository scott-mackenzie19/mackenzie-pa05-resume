//
// Created by Kate Bouis on 11/13/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_F
using namespace std;

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
    void insert (AvlNode*&, const T&);
    bool contains (AvlNode* c, int val) {
        if (c == nullptr) return false;
        else if (c->data == element) return true;
        else if (val < c-> data) return contains (c-> left, val);
        else return contains (c-> right, val);
    }
    DSAvlTree(const DSAvlTree<T>&) {}
    DSAvlTree<T>& operator=(const DSAvlTree<T>&) {}
public:
    DSAvlTree(): root(nullptr) {}
    DSAvlTree(const DSAvlTree& rhs): root(nullptr) { *this = rhs}
    ~DSAvlTree() {makeEmpty(root);}
    void makeEmpty(AvlNode*);
    AvlNode* insert (const T& x) {insert (x, root);}
    void balance (AvlNode*&);
    void rotateWithLeftChild (AvlNode*&)
    void rotateWithRightChild (AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void doubleWithRightChild(AvlNode*&);
    int height (AvlNode*);
    int max (int, int);
    bool contains (T val) {return contains (root, val);}
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
AvlNode* DSAvlTree<T>::insert (AvlNode*& t, const T& x) {
    if (contains(x)) return t;
    if (t==nullptr) t = new AvlNode (x, nullptr, nullptr);
    else if (x < t->element) insert (x, t-> left);
    else if (t -> element < x) insert (x, t -> right);
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
void rotateWithLeftChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> left;
    k2-> left = k1-> right;
    k1->right = k2;
    k2->height = max (height(k2->left), height (k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
template <typename T>
void rotateWithRightChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> right;
    k2->right = k1 -> left;
    k1-> left = k2;
    k2 -> height = max (height(k2->right), height (k2->left)) + 1;
    k1->height = max (height(k1->right), k2->height)+1;
    k2 = k1;
}
template <typename T>
void doubleWithLeftChild(AvlNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild (k3);
}
template <typename T>
void doubleWithRightChild(AvlNode*& k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild (k3);
}

template <typename T>
int DSAvlTree<T>::max (int a, int b) {
    if (a>=b) return a;
    else return b;
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
