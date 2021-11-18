//
// Created by Kate Bouis on 11/13/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_F

template <typename K, typename V>
class DSAvlTree{
private:
    class AvlNode {
    public:
        K key;
        V val;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode(const K& theKey, const V& theVal, AvlNode* lt, AvlNode* rt, int h = 0): key(theKey), val(theVal), left(lt), right (rt), height (h) {}
    };
    AvlNode* root;
    K& insertPrivate (AvlNode*&, const K&, const V&);
    bool containsPrivate (AvlNode* c, K element) {
        if (c == nullptr) return false;
        else if (c->key == element) return true;
        else if (element < c-> key) return containsPrivate (c-> left, element);
        else return containsPrivate (c-> right, element);
    }
    DSAvlTree(const DSAvlTree<K, V>& rhs) {}
    DSAvlTree<K, V>& operator=(const DSAvlTree<K, V>& rhs) {}
public:
    DSAvlTree(): root(nullptr) {}
    ~DSAvlTree() {makeEmpty(root);}
    void makeEmpty(AvlNode*);
    K& insert (const K& x, const V& y) {return insertPrivate (root, x, y);}
    void balance (AvlNode*&);
    void rotateWithLeftChild (AvlNode*&);
    void rotateWithRightChild (AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void doubleWithRightChild(AvlNode*&);
    int height (AvlNode*);
    int max (int, int);
    bool contains (K element) {return containsPrivate (root, element);}
};

template <typename K, typename V>
void DSAvlTree<K, V>::makeEmpty(AvlNode* n) {
    if (n) {
        makeEmpty(n->left);
        makeEmpty(n->right);
        delete n;
    }
}
template <typename K, typename V>
int DSAvlTree<K, V>::height (AvlNode* n) {
    if (n == nullptr) return 0;
    return n->height;
}

template <typename K, typename V>
void DSAvlTree<K, V>::balance (AvlNode*& t) {
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

template <typename K, typename V>
void DSAvlTree<K, V>::rotateWithLeftChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> left;
    k2-> left = k1-> right;
    k1->right = k2;
    k2->height = max (height(k2->left), height (k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
    k1->height =max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) +1;
}

template <typename K, typename V>
void DSAvlTree<K, V>::rotateWithRightChild (AvlNode*& k2) {
    AvlNode* k1 = k2-> right;
    k2->right = k1 -> left;
    k1-> left = k2;
    k2 -> height = max (height(k2->right), height (k2->left)) + 1;
    k1->height = max (height(k1->right), k2->height)+1;
    k2 = k1;
    k1->height =max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) +1;
}
template <typename K, typename V>
void DSAvlTree<K, V>::doubleWithLeftChild(AvlNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild (k3);
}
template <typename K, typename V>
void DSAvlTree<K, V>::doubleWithRightChild(AvlNode*& k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild (k3);
}

template <typename K, typename V>
int DSAvlTree<K, V>::max (int a, int b) {
    if (a>=b) return a;
    else return b;
}

// help w this
template<typename K, typename V>
K& DSAvlTree<K, V>::insertPrivate(AvlNode*& t, const K& x, const V& y) {
    if (contains(x)) {
        // add y to that x value
        return x;
    }
    else if (t==nullptr) {
        t = new AvlNode (x, y, nullptr, nullptr);
        return t->element;
    }
    else if (x < t->element) {
        int& temp = insertPrivate (t->left, x, y);
        balance (t);
        return temp;
    }
    else if (t -> element < x) {
       int& temp= insertPrivate (t -> right, x, y);
       balance (t);
       return temp;
    }
    t->height = 1 + max (height (t->left), height (t-> right));
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
