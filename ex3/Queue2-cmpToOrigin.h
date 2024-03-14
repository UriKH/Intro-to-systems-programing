#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>

template <typename T>
struct Node{
    T m_data;
    Node* m_next;

    explicit Node(const T& data) : m_data(data), m_next(nullptr){}; // this was T data before
};

template <typename T>
class Queue {
public:
    Queue();
    Queue(const Queue& other);
    ~Queue();

    void pushBack(const T& data); // I changed this to const T& instead of T
    void popFront();

    T& front();
    const T& front() const;
    int size() const;

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    
    class Iterator;
    Iterator begin();
    Iterator end();

    class EmptyQueue{};

    Queue& operator=(const Queue& other);
private:
    Node<T>* m_tail, *m_head;
    int m_size;

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
    ConstIterator& operator++();
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
    T& operator*();
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;

    class InvalidOperation{}; // empty invalid operation error
};

// __________________________________ Implemntation __________________________________


// __________________________________ Node __________________________________
// template <typename T>
// Node<T>::Node(T data, Node* next) : m_data(data), m_next(next){}

// __________________________________ Queue __________________________________
template <typename T>
Queue<T>::Queue() : m_tail(nullptr), m_head(nullptr), m_size(0){}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) : m_tail(nullptr), m_head(nullptr), m_size(0){
    Queue<T> temp;
    for (typename Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it){
        try{
            temp.pushBack(*it);
        }
        catch (const std::bad_alloc& e){
            while (m_size > 0){
                removeNode(temp.m_head);
            }
            throw;
        }
    }

    m_head = temp.m_head;
    m_tail = temp.m_tail;
    m_size = temp.m_size;

    temp.m_head = nullptr;
    temp.m_tail = nullptr;
    temp.m_size = 0;
}

template <typename T>
Queue<T>::~Queue(){
    while (m_size > 0){
        removeNode(m_head);
        m_size--;
    }
}

template <typename T>
void Queue<T>::pushBack(const T& data){
    Node<T>* newNode;
    try{
        newNode = new Node<T>(data);
    }
    catch (const std::bad_alloc& exception){
        throw;
    }

    if (m_head == nullptr){
        m_head = newNode;
    }
    else{
        if (m_tail == nullptr){
            m_tail = newNode;
            m_head->m_next = m_tail;
        }
        else{
            m_tail->m_next = newNode;
            m_tail = newNode;
        }
    }
    m_size++;
}

template <typename T>
T& Queue<T>::front(){
    if (m_size == 0){
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template <typename T>
const T& Queue<T>::front() const{
    if (m_size == 0){
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template <typename T>
void Queue<T>::popFront(){
    if (m_size == 0){
        throw EmptyQueue();
    }
    if (m_head != nullptr){
        removeNode(m_head);
        m_size--;
        
        if (m_size == 0){
            m_head = nullptr;
            m_tail = nullptr;
        }
    }
}

template <typename T>
int Queue<T>::size() const{
    return m_size;
}

// is there a simpler way?
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

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    if (this == &other){
        return *this;
    }

    Queue<T> temp = Queue(other);
    // for (typename Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it){
    //     try{
    //         temp.pushBack(*it);
    //     }
    //     catch (const std::bad_alloc& e){
    //         while (m_size > 0){
    //             removeNode(temp.m_head);
    //         }
    //         throw;
    //     }
    // }

    Node<T>* tempFront = m_head;
    Node<T>* tempRear = m_tail;
    int tempLength = m_size;

    m_head = temp.m_head;
    m_tail = temp.m_tail;
    m_size = temp.m_size;

    temp.m_head = tempFront;
    temp.m_tail = tempRear;
    temp.m_size = tempLength;

    tempFront = nullptr;
    tempRear = nullptr;
    tempLength = 0;

    // while (m_size > 0){
    //     removeNode(m_head);
    // }

    // m_head = temp.m_head;
    // m_tail = temp.m_tail;
    // m_size = temp.m_size;

    // temp.m_size = 0;
    return *this;
}


// __________________________________ Queue nonmember functions __________________________________
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

// __________________________________ Queue iterators __________________________________
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin(){
    return Queue<T>::Iterator(this, m_head);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end(){
    return Queue<T>::Iterator(this, nullptr);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const{
    return Queue<T>::ConstIterator(this, m_head);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const{
    return Queue<T>::ConstIterator(this, nullptr);
}

// __________________________________ ConstIterator __________________________________
template <typename T>
Queue<T>::ConstIterator::ConstIterator(const Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}

template <typename T>
const T& Queue<T>::ConstIterator::operator*() const{
    if (m_node == nullptr){
        throw InvalidOperation();
    }
    return m_node->m_data;
}

template <typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
    if (m_node == nullptr){
        throw InvalidOperation();
    }

    m_node = m_node->m_next;
    return *this;
}

template <typename T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const{
    if (m_queue != it.m_queue){
        throw InvalidOperation();
    }
    return m_node != it.m_node;
}

// __________________________________ Iterator __________________________________
template <typename T>
Queue<T>::Iterator::Iterator(Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}

template <typename T>
T& Queue<T>::Iterator::operator*(){
    if (m_node == nullptr){
        throw InvalidOperation();
    }
    return m_node->m_data;
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    if (m_node == nullptr){
        throw InvalidOperation();
    }

    m_node = m_node->m_next;
    return *this;
}

template <typename T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const{
    if (m_queue != it.m_queue){
        throw InvalidOperation();
    }
    return m_node != it.m_node;
}



#endif // QUEUE_H