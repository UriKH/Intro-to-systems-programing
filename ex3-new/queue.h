#ifndef QUEUE_H
#define QUEUE_H


#include <iostream>
#include <stdexcept>

template <typename T>
struct Node{
    T m_data;
    Node* m_next;

    explicit Node(const T& data) : m_data(data), m_next(nullptr){}
};

template <typename T>
class Queue{
    Node<T>* m_head;
    int m_size;

public:
    explicit Queue() : m_head(nullptr), m_size(0){}

    Queue(const Queue& other) : m_head(nullptr), m_size(0){
        *this = other;
        // Node<T>* tempHead = other.m_head;
        // while (tempHead != nullptr){
        //     this->pushBack(tempHead->m_data);
        //     tempHead = tempHead->m_next;
        // }
    }

    ~Queue(){
        // while (m_head != nullptr){
        //     this->popFront();
        // }
        // m_head = nullptr;
        Node<T>* current = m_head;
        Node<T>* next;

        while (current != nullptr){
            next = current->m_next;
            delete current;
            current = next;
        }
        m_head = nullptr;
    }

    void pushBack(const T& data){
        Node<T>* newNode = new Node<T>(data);

        if (m_head == nullptr){
            m_head = newNode;
        }
        else{
            Node<T>* temp = m_head;
            while (temp->m_next != nullptr){
                temp = temp->m_next;
            }
            temp->m_next = newNode;
        }
        m_size++;
    }

    void popFront(){
        if (m_size == 0){
            throw EmptyQueue();
        }
        Node<T>* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
        m_size--;
    }

    int size() const{
        return m_size;
    }

    T& front(){
        if (m_size == 0){
            throw EmptyQueue();
        }
        return m_head->m_data;
    }

    const T& front() const{
        if (m_size == 0){
            throw EmptyQueue();
        }
        return m_head->m_data;
    }

    Queue& operator=(const Queue& other){
        if (this == &other){
            return *this;
        }

        Queue<T> tempQueue;
        Node<T>* tempHead = other.m_head;

        while (tempHead != nullptr){
            tempQueue.pushBack(tempHead->m_data);
            tempHead = tempHead->m_next;
        }

        tempHead = m_head;
        m_head = tempQueue.m_head;
        m_size = tempQueue.m_size;
        tempQueue.m_head = tempHead;
        return *this;
    }

    class EmptyQueue{};

    class Iterator;
    Iterator begin(){
        return Iterator(this, m_head);
    }
    Iterator end(){
        return Iterator(this, nullptr);
    }

    class ConstIterator;
    ConstIterator begin() const{
        return ConstIterator(this, m_head);
    }
    ConstIterator end() const{
        return ConstIterator(this, nullptr);
    }
};

template <typename T>
class Queue<T>::Iterator{
    const Queue<T>* const m_queue;
    Node<T>* m_node;

    explicit Iterator(Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}
    friend class Queue;
public:
    class InvalidOperation{};

    T& operator*(){
        if (m_node == nullptr){
            throw InvalidOperation();
        }
        return m_node->m_data;
    }

    Iterator& operator++(){
        if (m_node == nullptr){
            throw InvalidOperation();
        }
        m_node = m_node->m_next;
        return *this;
    }

    bool operator!=(const Iterator& it) const{
        if (m_queue != it.m_queue){
            throw InvalidOperation();
        }
        return m_node != it.m_node;
    }
};

template <typename T>
class Queue<T>::ConstIterator{
    const Queue<T>* const m_queue;
    const Node<T>* m_node;

    explicit ConstIterator(const Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}
    friend class Queue;
public:
    class InvalidOperation{};

    const T& operator*() const{
        if (m_node == nullptr){
            throw InvalidOperation();
        }
        return m_node->m_data;
    }

    ConstIterator& operator++(){
        if (m_node == nullptr){
            throw InvalidOperation();
        }
        m_node = m_node->m_next;
        return *this;
    }

    bool operator!=(const ConstIterator& it) const{
        if (m_queue != it.m_queue){
            throw InvalidOperation();
        }
        return m_node != it.m_node;
    }
};

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate predicate){
    Queue<T> result;
    for (typename Queue<T>::ConstIterator it = source.begin(); it != source.end(); ++it){
        if (predicate(*it)){
            result.pushBack(*it);
        }
    }

    return result;
}

template <typename T, typename Function>
void transform(Queue<T>& source, Function function){
    Queue<T> copy;
    for (typename Queue<T>::Iterator it = source.begin(); it != source.end(); ++it){
        copy.pushBack(function(*it));
    }
    source = copy;
}

template <typename T, typename V, typename Function>
V reduce(const Queue<T>& source, const V& startValue, Function function){
    V result = startValue;
    for (typename Queue<T>::ConstIterator it = source.begin(); it != source.end(); ++it){
        result = function(result, *it);
    }
    return result;
}

#endif