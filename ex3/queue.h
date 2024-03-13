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
    Queue(const Queue<T>& other);
    ~Queue();

    // should put new node at the rear of the queue
    void pushBack(T data);
    void popFront(); // removes the front node from the queue
    T& front() const; // return the first nodes data in the queue
    int size() const; // return the size of the queue

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    
    class Iterator;
    Iterator begin();
    Iterator end();

    class EmptyQueue{}; // empty queue error

    Queue<T>& operator=(const Queue<T>& other);
private:
    Node<T>* m_rearNode, *m_frontNode;
    int m_length;

    static void removeNode(Node<T>* node);
};

template <typename T>
class Queue<T>::ConstIterator{
    const Queue<T>* m_queue;
    Node<T>* m_node;

    ConstIterator(const Queue<T>* queue, Node<T>* Node);
    friend class Queue<T>;
public:
    const T& operator*() const;
    ConstIterator operator++();
    bool operator!=(const ConstIterator& it) const;

    class InvalidOperation{}; // empty invalid operation error
};

template <typename T>
class Queue<T>::Iterator{
    const Queue<T>* m_queue;
    Node<T>* m_node;

    Iterator(Queue<T>* queue, Node<T>* Node);
    friend class Queue<T>;
public:
    T& operator*() const;
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
Queue<T>::Queue(const Queue<T>& other) : m_rearNode(nullptr), m_frontNode(nullptr), m_length(0){
    for (typename Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it){
        this->pushBack(*it);
    }
}

template <typename T>
Queue<T>::~Queue(){
    while (m_length > 0){
        removeNode(m_frontNode);
        m_length--;
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
    if (m_length == 0){
        throw EmptyQueue();
    }
    if (m_frontNode != nullptr){
        removeNode(m_frontNode);
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

template <typename T>
void Queue<T>::removeNode(Node<T>* node){
    if (node->m_next == nullptr){
        delete node;
    }
    else{
        Node<T>* temp = node->m_next;
        node->m_data = node->m_next->m_data;
        node->m_next = node->m_next->m_next;
        delete temp;
    }
}

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate predicate) {
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
        *it = function(*it);
    }
}

template <typename T, typename Function>
T reduce(const Queue<T>& source, const T& startValue, Function function){
    T result = startValue;
    for (typename Queue<T>::ConstIterator it = source.begin(); it != source.end(); ++it){
        result = function(result, *it);
    }
    return result;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin(){
    return Queue<T>::Iterator(this, m_frontNode);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end(){
    return Queue<T>::Iterator(this, nullptr);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const{
    return Queue<T>::ConstIterator(this, m_frontNode);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const{
    return Queue<T>::ConstIterator(this, nullptr);
}


template <typename T>
Queue<T>::ConstIterator::ConstIterator(const Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}

template <typename T>
const T& Queue<T>::ConstIterator::operator*() const{
    if (m_node == nullptr){
        throw ConstIterator::InvalidOperation();
    }
    return m_node->m_data;
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(){
    if (m_node == nullptr){
        throw InvalidOperation();
    }

    ConstIterator result = *this;
    m_node = m_node->m_next;
    return result;
}

template <typename T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const{
    if (m_queue != it.m_queue){
        throw InvalidOperation();
    }
    return m_node != it.m_node;
}

template <typename T>
Queue<T>::Iterator::Iterator(Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}

template <typename T>
T& Queue<T>::Iterator::operator*() const{
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
        throw Iterator::InvalidOperation();
    }
    return m_node != it.m_node;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    if (this == &other){
        return *this;
    }

    while (m_length > 0){
        removeNode(m_frontNode);
    }
    *this = Queue(other);
    return *this;
}

#endif // QUEUE_H