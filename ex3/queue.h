#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
class Node {
public:
    Node() = default;
    Node(T data, Node* next = nullptr) : m_data(data), m_next(next){};

private:
    T m_data;
    Node* m_next;
    void popNode(Node* previous); // removes the node
};

template <typename T>
void Node<T>::popNode(Node* previous) {
    if(previous != nullptr){
        previous->m_next = m_next;
    }
    delete this;
}

template <typename T>
class Queue {
    public:
        Queue();
        ~Queue();
        void pushBack(T data); // should put new node at the rear of the queue
        void popFront(); // removes the front node from the queue
        T front(); // return the first nodes data in the queue
        int size(); // return the size of the queue

        class EmptyQueue{};

private:
        Node<T>* m_rearNode, *m_frontNode;
        int m_length;
};

template <typename T>
Queue<T>::Queue() : m_length(0), m_rearNode(nullptr), m_frontNode(nullptr){}

template <typename T>
Queue<T>::~Queue(){
    while (size > 0){
        this->popFront();
    }
}


template <typename T>
void Queue<T>::pushBack(T data){
    Node<T>* newNode;
    try{
        newNode = new Node<T>(data);
    }
    catch (std::bad_alloc& exception){
        throw;
    }

    if (m_frontNode == nullptr) {
        m_frontNode = newNode;
    } else {
        if(m_rearNode == nullptr){
            m_rearNode = newNode;
            m_frontNode->m_next = m_rearNode;
        } else {
            m_rearNode->m_next = newNode;
            m_rearNode = newNode;
        }
    }
    m_length++;
}

template <typename T>
T Queue<T>::front(){
    if (m_length == 0){
        throw EmptyQueue();
    }
    return m_frontNode->m_data;
}

template <typename T>
void Queue<T>::popFront() {
    if (m_frontNode != nullptr) {
        Node<T>* temp = m_frontNode;
        m_frontNode->popNode(nullptr);
        m_frontNode = temp->m_next;
        delete temp;
        m_length--;
    }
}

template <typename T>
int Queue<T>::size() {
    return m_length;
}

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate predicate) {
    Queue<T> result;
    Node<T>* current = source.m_frontNode;

    while (current != nullptr) {
        if (predicate(current->m_data)){
            result.pushBack(current->m_data);
        }
        current = current->m_next;
    }

    return result;
}

#endif // QUEUE_H