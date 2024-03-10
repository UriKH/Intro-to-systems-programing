#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Node {
public:
    Node() = default;
    Node(T data);
    Node(T data, Node* previous);

private:
    T data;
    Node* next, *previous;
    void popNode(); // removes the node
};

template <typename T>
Node<T>::Node(T data) : data(data), previous(nullptr){}

template <typename T>
Node<T>::Node(T data, Node *previous) : data(data), previous(previous){}

template <typename T>
void Node<T>::popNode() {
    if (previous != nullptr) {
        previous->next = next;
        if (next != nullptr) {
            next->previous = previous;
        }
        delete this;
    }
}

template <typename T>
class Queue {
    public:
        Queue() = default;
        void pushBack(T data); // should put new node at the rear of the queue
        T front(); // return the first nodes data in the queue
        void popFront(); // removes the front node from the queue
        int size(); // return the size of the queue

    private:
        Node<T>* rearNode, *frontNode;
};

template <typename T>
void Queue<T>::pushBack(T data) {
    Node<T>* newNode = new Node<T>(data);

    if (rearNode == nullptr) {
        rearNode = newNode; // not sure how to implement corrcetly if the queue size is 1
        frontNode = newNode; // maybe like this?
    } else {
        rearNode->next = newNode;
        newNode->previous = rearNode;
        rearNode = newNode;
    }
}

template <typename T>
T Queue<T>::front() {
    if (front != nullptr) {
        return frontNode->data;
    } else {
    // nee to handle this correfctly, not sure how to do that yet
    }
}

template <typename T>
void Queue<T>::popFront() {
    if (frontNode != nullptr) {
        Node<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode != nullptr) {
            frontNode->previous = nullptr;
        } else {
            rearNode = nullptr;
        }
        temp->popNode(); // Use the popNode function to safely delete the node
    }
}

template <typename T>
int Queue<T>::size() {
    int count = 0;
    Node<T>* current = frontNode;
    while (current != nullptr) { // need to find a way to make sure it isnt infinite loop
        count++;
        current = current->next;
    }
    return count;
}

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate pred) {
    Queue<T> result;
    Node<T>* current = source.front;

    while (current != nullptr) {
        if (pred(current->data)) {
            result.pushBack(current->data);
        }
        current = current->next;
    }

    return result;
}


template <typename T>
Queue<T>* filter(){ // should filter out the nodes that doesn not statisfy the condition

}

#endif // QUEUE_H