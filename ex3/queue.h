#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
struct Node{
    T m_data;
    Node* m_next;

    Node() = default;
    Node(T data, Node* next = nullptr);
};

template <typename T>
class Queue {
public:
    Queue();
    ~Queue();

    // should put new node at the rear of the queue
    void pushBack(T data);
    void popFront(); // removes the front node from the queue
    T& front() const; // return the first nodes data in the queue
    int size() const; // return the size of the queue

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    
    class EmptyQueue{}; // empty queue error
private:
    Node<T>* m_rearNode, * m_frontNode;
    int m_length;
};

template <typename T>
class Queue<T>::Iterator{
    const Queue<T>* m_queue;
    Node<T>* m_node;

    Iterator(const Queue<T>* queue, Node<T>* Node);
    friend class Queue<T>;
public:
    const T& operator*() const;
    Iterator operator++();
    bool operator!=(const Iterator& it) const;

    class InvalidOperation{}; // empty invalid operation error
};

// ------- Implemntation -------

template <typename T>
Node<T>::Node(T data, Node* next) : m_data(data), m_next(next){}

template <typename T>
Queue<T>::Queue() : m_rearNode(nullptr), m_frontNode(nullptr), m_length(0){}

template <typename T>
Queue<T>::~Queue(){
    while (m_length > 0){
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

    if (m_frontNode == nullptr){
        m_frontNode = newNode;
    }
    else{
        if (m_rearNode == nullptr){
            m_rearNode = newNode;
            m_frontNode->m_next = m_rearNode;
        }
        else{
            m_rearNode->m_next = newNode;
            m_rearNode = newNode;
        }
    }
    m_length++;
}

template <typename T>
T& Queue<T>::front() const{
    if (m_length == 0){
        throw EmptyQueue();
    }
    return m_frontNode->m_data;
}

template <typename T>
void Queue<T>::popFront(){
    if (m_frontNode != nullptr){
        if (m_frontNode->m_next == nullptr){
            delete m_frontNode;
            
        }
        else{
            Node<T>* temp = m_frontNode->m_next;
            m_frontNode->m_data = m_frontNode->m_next->m_data;
            m_frontNode->m_next = m_frontNode->m_next->m_next;
            delete temp;
        }
        m_length--;
        
        if (m_length == 0){
            m_frontNode = nullptr;
            m_rearNode = nullptr;
        }
    }
}

template <typename T>
int Queue<T>::size() const{
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

template <typename T, typename Predicate>
void transform(Queue<T>& source, Predicate predicate){
    Queue<T> copy;
    for (typename Queue<T>::Iterator it = source.begin(); it != source.end(); ++it){
        copy.pushBack(*it);
    }

    while (source.size() > 0){
        source.popFront();
    }

    for (typename Queue<T>::Iterator it = copy.begin(); it != copy.end(); ++it){
        source.pushBack(predicate(*it));
    }
}

template <typename T, typename Function>
T reduce(const Queue<T>& source, const T& startValue, Function function){
    T result = startValue;
    for (typename Queue<T>::Iterator it = source.begin(); it != source.end(); ++it){
        result = function(result, *it);
    }
    return result;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Queue<T>::Iterator(this, m_frontNode);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    return Queue<T>::Iterator(this, nullptr);
}

template <typename T>
Queue<T>::Iterator::Iterator(const Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}

template <typename T>
const T& Queue<T>::Iterator::operator*() const{
    if (m_node == nullptr){
        throw InvalidOperation();
    }
    return m_node->m_data;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(){
    if (m_node == nullptr){
        throw InvalidOperation();
    }

    Iterator result = *this;
    m_node = m_node->m_next;
    return result;
}

template <typename T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const{
    if (m_queue != it.m_queue){
        throw InvalidOperation();
    }
    return m_node != it.m_node;
}

#endif // QUEUE_H