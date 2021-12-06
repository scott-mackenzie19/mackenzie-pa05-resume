//
// Created by Kate Bouis on 11/13/21.
//
// https://aozturk.medium.com/simple-hash-map-hash-table-implementation-in-c-931965904250
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H

#define TABLE_SIZE 100043
#include <string>
#include <stdexcept>
#include<vector>
#include <unordered_set>
#include <functional>

using namespace std;

template <typename K>
struct KeyHash {
    // https://stackoverflow.com/questions/6709795/converting-string-to-ascii
    int operator()(const K& key) const {
        return std::hash<std::string>{}(key) % TABLE_SIZE;
    }
};

template <typename K, typename V, typename F = KeyHash<K>>
class DSHash {
private:
    class HashNode {
    private:
        K key;
        V value;
        HashNode *next;
    public:
        HashNode () {key = {}; value = {}; next = nullptr; }
        HashNode (const K& key) { this->key = key; value = {}; next = nullptr; }
        HashNode (const K& key, const V& value) : key(key), value (value), next(nullptr) {}
        K getKey() const{
            return key;
        }
        V& getValue() {
            return value;
        }
        void setValue (V value) {
            HashNode::value = value;
        }
        HashNode *getNext() const {
            return next;
        }

        void setNext(HashNode * next) {
            HashNode::next = next;
        }

        bool operator==(HashNode* other) {
            return this->key == other->key;
        }
    };
    vector<HashNode*> table[TABLE_SIZE];
    F hashFunc;

public:
    DSHash() {}

    V& at (K& key) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;
        for (int i = 0; i < table[loc].size(); i++) {
            if (table[loc][i]->getKey() == key)
                return table[loc][i]->getValue();
        }

        throw std::range_error{"Key not found!"};
    }

    bool get (const K& key) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;
        for (int i = 0; i < table[loc].size(); i++) {
            if (table[loc][i]->getKey() == key)
                return true;
        }
        return false;
    }
    void put (const K& key, const V& value) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;

        HashNode* node = new HashNode(key, value);

        table[loc].push_back(node);
    }

    void remove (const K& key) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;

        HashNode* node = new HashNode(key);

        //table[loc];
    }
// https://stackoverflow.com/questions/25584065/hash-map-direct-access-operator
    V& operator [] (const K& key) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;
        for (int i = 0; i < table[loc].size(); i++) {
            if (table[loc][i]->getKey() == key)
                return table[loc][i]->getValue();
        }

        throw std::range_error{"Key not found!"};
    }

    vector<pair<K, V>> populateVector () {
        vector<pair<K, V>> vec;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                for (int j = 0; j < table[i].size(); j++) {
                    pair<K, V> p = pair<K, V>(table[i][j]->getKey(), table[i][j]->getValue());
                    vec.push_back(p);
                }
            }
        }
        return vec;
    }
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
