
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* start) : current(start) {}
        
        T& operator*() const {
            return current->data;
        }
        
        Iterator& operator++() {
            if (current)
                current = current->next;
            return *this;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    LinkedList();
    ~LinkedList();
    
    void add(T value);
    bool remove(int index);
    T get(int index) const;
    int getSize() const;
    bool isEmpty() const;
    
    Iterator begin() {
        return Iterator(head);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::add(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename T>
bool LinkedList<T>::remove(int index) {
    if (index < 0 || index >= size || head == nullptr) {
        return false; 
    }
    Node<T>* toDelete;
    if (index == 0) {
        toDelete = head;
        head = head->next;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }
    
    delete toDelete;
    size--;
    return true;
}

template <typename T>
T LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

#endif // LINKEDLIST_H
