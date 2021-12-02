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
using namespace std;

template <typename K>
struct KeyHash {
    // https://stackoverflow.com/questions/6709795/converting-string-to-ascii
    int operator()(const K& key) const {
        int ascii = 0;
        for (int i = 0; i < key.length(); i++) {
            char x = key.at(i);
            ascii+=int(x);
        }
        return ascii % TABLE_SIZE;
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
    };
    HashNode **table;
    F hashFunc;
public:
    DSHash() {
        table = new HashNode *[TABLE_SIZE]();
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }
    ~DSHash() {
//        for (int i = 0; i < TABLE_SIZE; i++) {
//            if (table[i] != nullptr)
//                delete table[i];
//        }
//        delete[] table;
    }
    DSHash(const DSHash<K, V>& copy) {
        HashNode ** newTable;
        for (int i = 0; i < TABLE_SIZE; i++) {
            newTable[i] == table[i];
        }
    }

    DSHash<K, V>& operator=(const DSHash<K, V>& copy) {
        HashNode ** newTable;
        for (int i = 0; i < TABLE_SIZE; i++) {
            newTable[i] == table[i];
        }
        return *this;
    }

    V& at (K& key) {
        auto hashValue = hashFunc(key);
        int loc = hashValue % TABLE_SIZE;
        return table[loc];
    }

    bool get (const K& key) {
        unsigned long hashValue = hashFunc (key);
        HashNode *entry = table [hashValue];
        while (entry!= nullptr) {
            if (entry->getKey() == key) {
                //value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }
    void put (const K& key, const V& value) {
        unsigned long hashValue = hashFunc (key);
        HashNode *prev = nullptr;
        HashNode *entry = table [hashValue];

        while (entry!=nullptr && entry->getKey() !=key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            entry = new HashNode(key, value);

            if (prev == nullptr)
                table[hashValue] = entry;
            else
                prev->setNext(entry);
        } else
            entry->setValue(value);
    }

    void remove (const K& key) {
        unsigned long hashValue = hashFunc (key);
        HashNode *prev = nullptr;
        HashNode *entry = table [hashValue];
        while (entry!=nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) return;
        else {
            if (prev == nullptr)
                table [hashValue] = entry->getNext();
            else
                prev->setNext(entry->getNext());
            delete entry;
        }
    }
// https://stackoverflow.com/questions/25584065/hash-map-direct-access-operator
    V& operator [] (const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode *entry = table[hashValue];
        while (entry != nullptr) {
            if (entry->getKey() == key) {
                return entry->getValue();
            }
            entry = entry->getNext();
        }
        throw std::range_error{"Key not found!"};
    }

    vector<pair<K, V>> populateVector () {
        vector<pair<K, V>> vec;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                pair<K, V> p = pair<K, V>(table[i]->key, table[i]->value);
                vec.push_back(p);
            }
        }
        return vec;
    }
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
