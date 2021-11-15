//
// Created by Kate Bouis on 11/13/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_F

template <typename T>
class DSAvlTree{
private:
    class AvlNode {
    public:
        T element;
        AvlNode* left;
        AvlNode* right;
        int height;
        AVLNode(const T& theElement, AvlNode* lt, AvlNode* rt, int h = 0): element (theElement), left(lt), right (rt), height (h) {}
    };
    AvlNode* root;
    void insert (AvlNode*&, const T&);
public:
    AvlTree(): root(NULL) {}
    AvlTree(const AvlTree& rhs): root(NULL) { *this = rhs}
    ~AvlTree() {makeEmpty();}
    void insert (const T& x) {insert (x, root);}
    void balance (AvlNode*&);
    void rotateWithLeftChild (AvlNode*&)
    void rotateWithRightChild (AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void rotateWithRightChild(AvlNode*&);
};

template <typename T>
void DSAvlTree<T>::insert (AvlNode*& t, const T& x) {
    if (t==nullptr) t = new AvlNode (x, nullptr, nullptr);
    else if (x < t->element) insert (x, t-> left);
    else if (t -> element < x) insert (x, t -> right);
    // if they're already equal add article to hash map of word already in tree
    balance (t);
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

void rotateWithLeftChild (AvlNode*&)
void rotateWithRightChild (AvlNode*&);
void doubleWithLeftChild(AvlNode*&);
void rotateWithRightChild(AvlNode*&);

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
