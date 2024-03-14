
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <assert.h>
#include <new>
#define START_SIZE 0

/**
 * @section generic node implementation
*/

template<class Element>
class Node
{
public:
    Element data;
    Node* next;
    explicit Node(const Element& data): data(data), next(nullptr){};
    ~Node() = default;
};



/**
 * @section LinkedList generic class
*/

template <class Element>
class LinkedList
{
private:
    Node<Element>* head;
public:
    LinkedList(): head(nullptr) {};

    Node<Element>* getHead() {  //head can be used for modifaction
        return (this->head);
    }

    Node<Element>* getHead() const{
        return (this->head);
    }

    void setHead(Node<Element>* newHead){
        this->head = newHead;
    }

    LinkedList(const LinkedList& other): head(nullptr) {
        if(this == &other){
            return;
        }

        // Copy each node from the other list

        Node<Element>* otherCurrent = other.getHead();
        while (otherCurrent != nullptr) {
            this->append(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }


    }

    LinkedList& operator=(const LinkedList& other){
        if(&other == this){
            return *this;
        }

        LinkedList<Element> tmp_list;
        Node<Element>* it = other.head;

        while (it != nullptr)
        {
            tmp_list.append(it->data);
            it = it->next;
        }

        //delete this; //TODO: why not work bro?!
        Node<Element>* tmp_swap = this->getHead();
        this->setHead(tmp_list.getHead());
        tmp_list.setHead(tmp_swap); // so it doesn't delete itself //TODO: make sure you can handle destractor of empty queue
        return *this;
    }

    // Destructor to free memory
    ~LinkedList() {
        Node<Element>* current = head;
        Node<Element>* next;

        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }


    // Function to append a new node to the end of the list
    void append(const Element& value) {

        Node<Element>* newNode = new Node<Element>(value);

        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            Node<Element >* current = this->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

    }

};


/**
 * @section Queue generic class
 */

template <class Element>//template <class T> // implment and test and then change to generic template!    
class Queue
{
private:
    LinkedList<Element> m_linkedList;
    int m_length;
public:
    // looking at example code => Big three are needed! c'tor, d'tor, copy c'tor
    /**
    * @brief c'tor with no params
    */
    Queue(): m_linkedList(), m_length(START_SIZE){};
    Queue(const Queue &other);
    Queue& operator=(const Queue<Element>& other){
        this->m_linkedList = other.m_linkedList;
        this->m_length = other.m_length;
        return *this;
    }
    //TODO: is operator = needed?

    ~Queue() = default;

    /**
     * @brief push to end of queue copy of val.
     * @note head of node is last input!
     */
    void pushBack(const Element& val){ // TODO : how to think about const and & !!
        this->m_linkedList.append(val);
        this->m_length++;
    }

    /**
     * @returns the front of the queue by value
    */
    Element& front(){
        if(this->m_length == START_SIZE){
            throw EmptyQueue();
        }
        return this->m_linkedList.getHead()->data;
    }

    /**
     * @returns the front of the queue by value
    */
    const Element& front() const{
        if(this->m_length == START_SIZE){
            throw EmptyQueue();
        }
        return this->m_linkedList.getHead()->data;
    }

    /**
     * @brief pops front of queue
     * @note doesn't return value of front.
     */
    void popFront(){
        if(this->m_length ==0){
            throw EmptyQueue();
        }
        Node<Element> * tmp_ptr = (this->m_linkedList.getHead());
        this->m_linkedList.setHead(this->m_linkedList.getHead()->next);
        this->m_length--;
        delete tmp_ptr;
    }
    /**
     * @returns number of elements in queue.
     * @returns 0 if empty.
     */
    int size() const{
        return this->m_length;
    }
    class Iterator;
    class ConstIterator;

    ConstIterator begin() const {
        return Queue<Element>::ConstIterator(this, this->m_linkedList.getHead());
    }
    ConstIterator end() const{
        return Queue<Element>::ConstIterator(this, nullptr); //default copy' ctor
    }

    Iterator begin() {
        return Queue<Element>::Iterator(this, this->m_linkedList.getHead());
    }
    Iterator end() {
        return Queue<Element>::Iterator(this, nullptr); //default copy' ctor
    }

    /**
     * @brief exeption class
     */
    class EmptyQueue
    {
    };
};



/**
 * @brief copy c'tor
*/
template <class Element>
Queue<Element>::Queue(const Queue& other){// :m_linkedList(other.m_linkedList), m_length(other.m_length){
    m_linkedList = other.m_linkedList;
    m_length = other.m_length;
}


/**
 * @section iterator implementation
 */

/**
 * @paragraph
 * standard minimum: *, +, !=
 * should support const iterators
 *
 */

template <class Element>
class Queue<Element>::Iterator
{
private:
    explicit Iterator(Queue *queue, Node<Element>* node_ptr) : queue(queue), node_ptr(node_ptr){}; // TODO: if queue is empty
    Queue<Element> *const queue; // the queue the interator points to.
    Node<Element>* node_ptr; // non const

public:

    Iterator(const Iterator& it) = default;
    Element& operator*(){
        if(this->node_ptr == nullptr){
            throw Queue::Iterator::InvalidOperation();
        }
        return this->node_ptr->data;
    }

    /**
    * @brief changes index and pointer to queue.
    */
    Iterator& operator++(){
        if (this->node_ptr == nullptr)
        {
            throw Queue::Iterator::InvalidOperation();
        }else {
            this->node_ptr = this->node_ptr->next;
        }
        return *this;
    }// pre fix

    bool operator!=(const Iterator& it) const{
        // assert(this->queue != it.queue); //TODO
        if(this->node_ptr != it.node_ptr){
            return true;
        }
        else{
            return false;
        }
    }

    class InvalidOperation
    {
    };
    friend class Queue; // allows queue to call c'tor
};




/**
 * @subsection const iterator implementation
 * -----------------------------------------
*/
template <class Element>
class Queue<Element>::ConstIterator
{
private:
    explicit ConstIterator(const Queue *queue_ptr, const Node<Element>* node_ptr) :
                queue_ptr(queue_ptr), node_ptr(node_ptr) {
    };

    const Queue<Element> *const queue_ptr; // the queue the interator points to.
    const Node<Element>* node_ptr;

public:
    const Element& operator*() const;
    ConstIterator(const ConstIterator& ) =default;
    /**
    * @brief changes index and pointer to queue.
    */
    ConstIterator& operator++(){
        if (this->node_ptr == nullptr)
        {
            throw Queue::ConstIterator::InvalidOperation();
        }else {
            this->node_ptr = this->node_ptr->next;
        }
        return *this;
    }// pre fix

    bool operator!=(const ConstIterator& it) const;

    class InvalidOperation
    {
    };
    friend class Queue; // allows queue to call c'tor
};



/**
 * @brief uses index to return value from queue.
 * @note can use the iterator to modify or read the value.
*/
template <class Element>
const Element& Queue<Element>::ConstIterator::operator*() const{
    if(this->node_ptr == nullptr)
    {
        throw Queue<Element>::ConstIterator::InvalidOperation();
    }

    return this->node_ptr->data;
}


template <class Element>
bool Queue<Element>::ConstIterator::operator!=(const ConstIterator &it) const
{
    if (this->node_ptr != it.node_ptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}






/**
 * @section queue methods
 */

/**
 * @brief deletes (filters out) elements.
 * @param queue
 * @param function_ptr
 * @return queue after filter is apllied.
*/

/**
 * @param selector return a bool value for each element.
 * @returns a queue without filtered elements.
*/
template <class Element, class Functor>
Queue<Element> filter(const Queue<Element> source, const Functor& selector){
    Queue<Element> filteredQueue;
    for (const Element element : source) { // TODO: ask harif about const correctness
    // 'element' represents each element in the queue
    // Perform actions on 'element'
        if(selector(element) == true){
           filteredQueue.pushBack(element);
        }
    }
    return filteredQueue;
}

/**
 * @brief changes values by place based on transformation
 * @param queue
 * @param transformation
 * @note we assume that transformation does not throw exeptions
*/
template <class Element, class Functor>
void transform(Queue<Element> & source, const Functor& transformation){
    Queue<Element> transformedQueue;
    for (Element& element : source){
    // 'element' represents each element in the queue
    // Perform actions on 'element'
        transformedQueue.pushBack(transformation(element)); //TODO: ask harif : bug found const corectness
    }
    source = transformedQueue;
}

/**
 * @param queue
 * @param startIndex
 * @param accoumlateFunctin
 * @note
*/

template <class Element, class S, class Functor>
S reduce(const Queue<Element> source,S startValue , const Functor& accumulate){
    S prevElement = startValue;
    for (const Element element : source){
        // 'element' represents each element in the queue
        // Perform actions on 'element'
        prevElement = accumulate(prevElement, element);
    }
    return prevElement;
}

#endif