#ifndef QUEUE_H
#define QUEUE_H


// ---------------------------------------------------------------------------------------------
// ------------------------------ DECLERATIONS AND PROTOTYPES ----------------------------------
// ---------------------------------------------------------------------------------------------

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
    }

    ~Queue();

    void pushBack(const T& data);
    void popFront();
    int size() const;
    T& front();
    const T& front() const;

    class EmptyQueue{};
    class Iterator;
    class ConstIterator;
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

    Queue& operator=(const Queue& other);
};

template <typename T>
class Queue<T>::Iterator{
    const Queue<T>* const m_queue;
    Node<T>* m_node;

    explicit Iterator(Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}
    friend class Queue;
public:
    T& operator*();
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;

    class InvalidOperation{};
};

template <typename T>
class Queue<T>::ConstIterator{
    const Queue<T>* const m_queue;
    const Node<T>* m_node;

    explicit ConstIterator(const Queue* queue, Node<T>* node) : m_queue(queue), m_node(node){}
    friend class Queue;
public:
    const T& operator*() const;
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& it) const;

    class InvalidOperation{};
};

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate predicate);

template <typename T, typename Function>
void transform(Queue<T>& source, Function function);

template <typename T, typename V, typename Function>
V reduce(const Queue<T>& source, const V& startValue, Function function);

// ---------------------------------------------------------------------------------------------
// ------------------------------------- IMPLEMENTATION ----------------------------------------
// ---------------------------------------------------------------------------------------------

// ___________________________________________ Queue ___________________________________________

template <typename T>
Queue<T>::~Queue(){
    Node<T>* temp;
    while (m_head != nullptr){
        temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
}

template <typename T>
void Queue<T>::pushBack(const T& data){
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

template <typename T>
void Queue<T>::popFront(){
    if (m_size == 0){
        throw EmptyQueue();
    }
    Node<T>* temp = m_head;
    m_head = m_head->m_next;
    m_size--;
    delete temp;
}

template <typename T>
int Queue<T>::size() const{
    return m_size;
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
Queue<T>& Queue<T>::operator=(const Queue& other){
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

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin(){
    return Iterator(this, m_head);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end(){
    return Iterator(this, nullptr);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const{
    return ConstIterator(this, m_head);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const{
    return ConstIterator(this, nullptr);
}

// ___________________________________________ Iterators ___________________________________________

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

// ___________________________________________ filter, transform, reduce ___________________________________________
template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate predicate){
    Queue<T> result;
    for (const T& value : source){
        if (predicate(value)){
            result.pushBack(value);
        }
    }
    return result;
}

template <typename T, typename Function>
void transform(Queue<T>& source, Function function){
    Queue<T> copy;
    for (T& value : source){
        copy.pushBack(function(value));
    }
    source = copy;
}

template <typename T, typename V, typename Function>
V reduce(const Queue<T>& source, const V& startValue, Function function){
    V result = startValue;
    for (const T& value : source){
        result = function(result, value);
    }
    return result;
}

#endif