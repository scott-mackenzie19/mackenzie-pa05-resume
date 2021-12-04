//
// Created by Kate Bouis on 11/13/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H
#define INC_21F_F
#include <iostream>
#include <queue>
#include <fstream>
#include <queue>
using namespace std;

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
        AvlNode(const K& theKey, AvlNode* lt, AvlNode* rt, int h = 0): key(theKey), left(lt), right (rt), height (h) {}
        AvlNode(const K& theKey, const V& theVal, AvlNode* lt, AvlNode* rt, int h = 0): key(theKey), val(theVal), left(lt), right (rt), height (h) {}
    };
    AvlNode* root;
    V& insertPrivate (AvlNode*&, const K&, V&);
    bool containsPrivate (AvlNode* c, K element) {
        if (c == nullptr) return false;
        else if (c->key == element) return true;
        else if (element < c-> key) return containsPrivate (c-> left, element);
        else return containsPrivate (c-> right, element);
    }
    DSAvlTree(const DSAvlTree<K, V>& rhs) {}
    V& findPrivate (AvlNode*&, const K&);

public:
    DSAvlTree(): root(nullptr) {}
    ~DSAvlTree() {makeEmpty(root);}
    void makeEmpty(AvlNode*);
    V& insert (const K& x, V& y) {return insertPrivate (root, x, y);}
    void balance (AvlNode*&);
    void rotateWithLeftChild (AvlNode*&);
    void rotateWithRightChild (AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void doubleWithRightChild(AvlNode*&);
    int height (AvlNode*);
    int max (int, int);
    bool contains (K element) {return containsPrivate (root, element);}
    vector<pair<K, V>> levelOrder (AvlNode*);
    vector <pair<K, V>> populateVector();
    K getKey() {return this->key;}
    DSAvlTree<K, V>& operator=(const DSAvlTree<K, V>& rhs) {}
    V& find (const K& x){return findPrivate(root, x);}
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

template<typename K, typename V>
V& DSAvlTree<K, V>::insertPrivate(AvlNode*& t, const K& x, V& y) {
    if (t==nullptr) {
        t = new AvlNode (x, y, nullptr, nullptr);
        t->height = 1 + max (height (t->left), height (t-> right));
        return t->val;
    }
    else if (x < t->key) {
        V& temp = insertPrivate (t->left, x, y);
        balance (t);
        t->height = 1 + max (height (t->left), height (t-> right));
        return temp;
    }
    else if (t -> key < x) {
       V& temp= insertPrivate (t -> right, x, y);
       balance (t);
        t->height = 1 + max (height (t->left), height (t-> right));
        return temp;
    }
    else return t->val;
}

template <typename K, typename V>
V& DSAvlTree<K, V>::findPrivate (AvlNode*& t, const K& x) {
    if (t==nullptr) {
        throw ("does not exist");
    }
    else if (x < t->key) {
        return findPrivate (t->left, x);
    }
    else if (t -> key < x) {
        return findPrivate (t -> right, x);
    }
    else return t->val;
}

template <typename K, typename V>
V& DSAvlTree<K, V>::findPrivate (AvlNode*& t, const K& x) {
    if (t==nullptr) {
        throw ("does not exist");
    }
    else if (x < t->key) {
        return findPrivate (t->left, x);
    }
    else if (t -> key < x) {
        return findPrivate (t -> right, x);
    }
    else return t->val;
}

template<typename K, typename V>
vector<pair<K, V>> DSAvlTree<K, V>::levelOrder (AvlNode* n) {
    cout << "in " << endl;
    queue<AvlNode*> q;
    q.push(n);
    vector<pair<K, V>> vec;
    while (!q.empty()) {
        AvlNode *curr = q.front();
        q.pop();
        if (curr->right != nullptr && curr->left != nullptr) {
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
            // print to file
            pair<K, V> p = pair<K, V>(q.front()->key, q.front()->val);
            vec.push_back(p);
        }
    }
    return vec;
}
template <typename K, typename V>
vector <pair<K, V>> DSAvlTree<K,V>::populateVector() {
    return levelOrder(root);
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSAVLTREE_H