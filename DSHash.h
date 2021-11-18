//
// Created by Kate Bouis on 11/13/21.
//
// https://www.journaldev.com/35238/hash-table-in-c-plus-plus
#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H

#include <cstring>
#include "DSLinkedList.h"

template <typename V>
class DSHash {
private:
    struct hashItem {
        char *key;
        V value;
    };
    struct hashTable{
        hashItem** items;
        DSLinkedList** overflowBuckets;
        int size;
        int count;
    };
public:
    DSHash() {}
    DSHash(const char*& k, const V& val):key(k), value(val), size(0), count(0) {}
    // key is string and value is vector of file objects containing either the person or org listed

    // copy constructor
    // overloaded assignment
    // destructor

    // map keys to values- hash function that sums ascii values
    int HashFunction(char*, V);

    //create item
    hashItem* createItem(char*, V);

    // create table
    hashTable* createTable(int);

    // free item
    void freeItem(hashItem*);

    //free table
    void freeTable(hashTable*);

    // account for collision of keys
    void collision(hashTable*, int, hashItem*);

    //insert
    void hashInsert(hashTable*, char*, V);

    // search
    char* hashSearch(hashTable*, char*);

    // delete
    void hashDelete(hashTable*, char*);

};

template <typename V>
int DSHash<V>::HashFunction(char* k, V val){
    int i = 0;
    for (int j = 0; k[j]; j++)
        i += k[j];
    return i % 100;
}

template <typename V>
hashItem* DSHash<V>::createItem(char* key, V value) {
    // Creates a pointer to a new hash table item
    hashItem *item = (hashItem *) malloc(sizeof(hashItem));
    item->key = (char *) malloc(strlen(key) + 1);
    item->value = (V) malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

template <typename V>
hashTable* DSHash<V>::createTable(int size) {
    // Creates a new HashTable
    hashTable* table = (hashTable*) malloc (sizeof(hashTable));
    table->size = size;
    table->count = 0;
    table->items = (hashItem**) calloc (table->size, sizeof(hashItem*));
    for (int i=0; i< table->size; i++)
        table->items[i] = nullptr;
    table->overflowBuckets = createOverflowBuckets(table);
    return table;
}

template <typename V>
void DSHash<V>::freeItem(hashItem* item) {
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}

template <typename V>
void DSHash<V>::freeTable(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        hashItem* item = table->items[i];
        if (item != nullptr)
            free_item(item);
    }
    freeOverflowBuckets(table);
    free(table->items);
    free(table);
}

templatae <typename V>
void DSHash<V>::collision(hashTable* table, int index, hashItem* item) {
    DSLinkedList* head = table->overflowBuckets[index];
    if (head == nullptr){
        //create list
        head = (DSLinkedList*) malloc (sizeof(DSLinkedList));
        head -> item = item;
        table->overflowBuckets[index] = head;
        return;
    } else {
        table->overflowBuckets[index] = insertFront(item);
        return;
    }
}

template <typename V>
void DSHash<V>::hashInsert(hashTable* table, char* key, V value) {
    // Create the item
    hashItem* item = createItem(key, value);

    hashItem* curr = table->items[index];

    if (curr == nullptr) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            return;
        }
        // Insert directly
        table->items[index] = item;
        table->count++;
    }

    else {
        // Scenario 1: We only need to update value
        if (strcmp(current->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        }

        else {
            // Scenario 2: Collision
            // We will handle case this a bit later
            collision(table, item);
            return;
        }
    }
}

template <typename V>
char* DSHash<V>::hashSearch(hashTable* table, char* key) {
    // Searches the key in the hashtable and returns nullptr if it doesn't exist
    int index = HashFunction(key);
    hashItem* item = table->items[index];
    DSLinkedList* head = table->overflowBuckets[index];

    // Ensure that we move to a non NULL item
    while (item!=nullptr) {
        if (strcmp(item->key, key) == 0)
            return item-> value;
        if (head == nullptr)
            return nullptr;
        item = head->item;
        head = head-> next;
    }
    return nullptr;
}

template <typename V>
void DSHash<V>::hashDelete(hashTable* table, char* key) {
    // Deletes an item from the table
    int index = HashFunction(key);
    DSItem* item = table->items[index];
    DSLinkedList* head = table->overflowBuckets[index];

    if (item == nullptr)
        return;
    else {
        if (head == nullptr && strcmp(item->key, key) == 0) {
            table->items[index] = nullptr;
            freeItem(item);
            table->count--;
            return;
        }
        else if (head != nullptr) {
            if (strcmp(item->key, key) == 0) {
                freeItem(item);
                DSLinkedList* node = head;
                head = head->next;
                node->next = nullptr;
                table->items[index] = createItem(node->item->key, node->item->value);
                LinkedList* temp = node;
                while (node) {
                    temp = node;
                    node = node->next;
                    free(temp->item->key);
                    free(temp->item->value);
                    free(temp->item);
                    free(temp);
                }
                table->overflowBuckets[index] = head;
                return;
            }

            DSLinkedList* curr = head;
            DSLinkedList* prev = nullptr;

            while (curr) {
                if (strcmp(curr->item->key, key) == 0) {
                    if (prev == nullptr) {
                        DSLinkedList* temp = head;
                        while (head) {
                            temp = head;
                            head = head->next;
                            free(temp->item->key);
                            free(temp->item->value);
                            free(temp->item);
                            free(temp);
                        }
                        table->overflowBuckets[index] = nullptr;
                        return;
                    }
                    else {
                        // This is somewhere in the chain
                        prev->next = curr->next;
                        curr->next = nullptr;
                        DSLinkedList* temp = curr;
                        while (curr) {
                            temp = curr;
                            curr = curr->next;
                            free(temp->item->key);
                            free(temp->item->value);
                            free(temp->item);
                            free(temp);
                        }
                        table->overflowBuckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }
        }
    }
}
#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSHASH_H
