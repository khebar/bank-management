
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
