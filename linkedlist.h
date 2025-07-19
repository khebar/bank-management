
#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T value):data(value),next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    
    void add(T value);
    bool remove(int index);
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