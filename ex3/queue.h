#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Node {
public:
    Node() = default;
    Node(T data, Node* next) : data(data), next(next) {};

private:
    T data;
    Node* next;
    void popNode(Node* previous); // removes the node
};

template <typename T>
void Node<T>::popNode(Node* previous) {
    if(previous != nullptr){
        previous->next = next;
    }
    delete this;
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
        int length;
};

template <typename T>
void Queue<T>::pushBack(T data) {
    Node<T>* newNode = new Node<T>(data, nullptr);

    if (frontNode == nullptr) {
        frontNode = newNode;
    } else {
        if(rearNode == nullptr){
            rearNode = newNode;
            frontNode->next = rearNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }
    length++;
}

template <typename T>
T Queue<T>::front() {
    if (frontNode != nullptr) {
        return frontNode->data;
    } else {
    // nee to handle this correfctly, not sure how to do that yet
    }
}

template <typename T>
void Queue<T>::popFront() {
    if (frontNode != nullptr) {
        Node<T>* temp = frontNode;
        frontNode->popNode(nullptr);
        frontNode = temp->next;
        delete temp;
        length--;
    }
}

template <typename T>
int Queue<T>::size() {
    return length;
}

template <typename T, typename Predicate>
Queue<T> filter(const Queue<T>& source, Predicate pred) {
    Queue<T> result;
    Node<T>* current = source.frontNode;

    while (current != nullptr) {
        if (pred(current->data)) {
            result.pushBack(current->data);
        }
        current = current->next;
    }

    return result;
}

#endif // QUEUE_H