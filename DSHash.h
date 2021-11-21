//
// Created by Kate Bouis on 11/13/21.
//
// https://aozturk.medium.com/simple-hash-map-hash-table-implementation-in-c-931965904250
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H

template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const {
        return reinterpret_cast<unsigned long>(key) % 5000;
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
        V getValue() const{
            return value;
        }
        void setValue (V value) {
            HashNode::value == value;
        }
        HashNode *getNext() const {
            return next;
        }
        void setNext(HashNode * next) {
            HashNode::next = next;
        }
    };
    HashNode <K, V> **table;
    F hashFunc;
public:
    DSHash();
    ~DSHash();
    bool get (const K&, V&);
    void put (const K&, const V&);
    void remove (const K&);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
