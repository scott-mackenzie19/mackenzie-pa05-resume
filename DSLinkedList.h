//
// Created by Kate Bouis on 11/18/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSLINKEDLIST_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSLINKEDLIST_H

#include "DSNode.h"
#include "DSHash.h"

template <typename T>
class DSLinkedList {
private:
    DSNode<T>* head;
    DSNode<T>* tail;
    DSNode<T>* curr;
    int size;

public:
    DSLinkedList();

    DSLinkedList(const DSLinkedList<T>&);

    DSLinkedList<T>& operator=(const DSLinkedList<T>&);

    ~DSLinkedList();

    bool isEmpty();

    void setCurrFront();
    void advanceCurr();
    void reverseCurr();
    DSNode<T>* getCurr();
    DSNode<T>* getHead();
    DSNode<T>* getTail();
    bool hasNext();

    void insertFront(T&);
    void insertEnd(T&);
    T pop();
    int getSize();

    DSLinkedList** createOverflowBuckets(hashTable*);
    void freeOverflowBuckets(hashTable*);
};

//default constructor
template<typename T>
DSLinkedList<T>::DSLinkedList() {
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    size = 0;
}

// copy constructor
template<typename T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& list) {
    DSNode<T>* temp = list.head;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    size = 0;
    while (temp != nullptr) {
        insertEnd(temp->x);
        temp = temp->next;
    }
}

// copy assignment operator
template<typename T>
DSLinkedList<T> &DSLinkedList<T>::operator=(const DSLinkedList<T>& list) {
    DSNode<T>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    curr = nullptr;
    size = 0;

    temp = list.head;
    while (temp != nullptr) {

        this->insertEnd(temp->x);
        temp = temp->next;
    }
    return *this;
}

// destructor
template<typename T>
DSLinkedList<T>::~DSLinkedList() {
    DSNode<T>* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    curr = nullptr;
    size = 0;
}

// checks if linked list is empty
template <typename T>
bool DSLinkedList<T>::isEmpty() {
    return head == nullptr;
}

// iterator functionalities, these functions all manipulate curr to iterate through linked list
template <typename T>
void DSLinkedList<T>::setCurrFront() {
    curr = head;
}
template <typename T>
void DSLinkedList<T>::advanceCurr() {
    curr = curr -> next;
}
template <typename T>
void DSLinkedList<T>::reverseCurr() {
    curr = curr -> prev;
}
template <typename T>
DSNode<T>* DSLinkedList<T>::getCurr() {
    return curr;
}

// gets first value of list
template <typename T>
DSNode<T>* DSLinkedList<T>::getHead() {
    return head;
}

// gets last value of list
template <typename T>
DSNode<T>* DSLinkedList<T>::getTail() {
    return tail;
}

// checks if the linked list has a value after curr
template <typename T>
bool DSLinkedList<T>::hasNext() {
    if (isEmpty()) return false;
    else return curr->next != nullptr;
}

// inserts value at end of linked list
//https://stackoverflow.com/questions/21267123/implementing-a-double-linked-list-in-c-pointers-and-odd-values
template <typename T>
void DSLinkedList<T>::insertEnd(T& val) {
    auto* newNode = new DSNode<T>();
    newNode->x = val;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        curr = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}

// inserts value at beginning of linked list
template <typename T>
void DSLinkedList<T>::insertFront(T& val) {
    auto* newNode = new DSNode<T>;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    newNode->x = val;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        curr = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;

    }
    head = newNode;
    size++;
}

// pops from front of linked list
template <typename T>
T DSLinkedList<T>::pop() {
    if (!isEmpty()) {
        T temp = head->x;
        DSNode<T>* del = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
            curr = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete del;

        size--;
        return temp;
    }
    else throw ("can't pop from empty list");
}

// gets size of linked list. this is achieved by making size variable, initializing to 0, and
// incrementing or decrementing every time insert or delete functions are called
template <typename T>
int DSLinkedList<T>::getSize(){
    return size;
}

DSLinkedList** createOverflowBuckets(hashTable* table) {
    DSLinkedList** buckets = (DSLinkedList**) calloc (table->size, sizeof(DSLinkedList*));
    for (int i=0; i<table->size; i++)
        buckets[i] = nullptr;
    return buckets;
}
void freeOverflowBuckets(hashTable* table) {
    DSLinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    DSLinkedList* temp = buckets;
    while (buckets) {
        temp = buckets;
        buckets = buckets->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSLINKEDLIST_H
