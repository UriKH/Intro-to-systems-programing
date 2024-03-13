#include <stdexcept>
#include <iostream>
#include <assert.h>
// #include <string>
// #include <vector>
// #include <array>
#include "queue.h"
#include "HealthPoints.h"
#define T int

using namespace std;


// ok
void testQcopyCtor(){
    Queue<int> q1;
    for (int i = 0; i < 5; i++){
        q1.pushBack(i);
    }
    assert(q1.size() == 5);

    Queue<int> q2(q1);
    const Queue<int> q3(q1);
    assert(q1.size() == 5);
    assert(q2.size() == 5);
    assert(q3.size() == 5);

    int i = 0;
    for (Queue<int>::Iterator it = q2.begin(); it != q2.end(); ++it){
        assert(*it == i);
        i += 2;
    }

    int i = 0;
    for (Queue<int>::ConstIterator it = q3.begin(); it != q3.end(); ++it){
        assert(*it == i);
        i += 2;
    }
}

// 
void testQinsertion(){
    Queue<int> q1, q2;
    for (int i = 0; i < 5; i++){
        q1.pushBack(i);
        q2.pushBack(i * 2);
    }

    q2.pushBack(10);
    q2.pushBack(12);

    assert(q1.size() == 5);
    assert(q2.size() == 7);
    q1 = q2;

    assert(q1.size() == 7);
    assert(q2.size() == 7);
}

void testEmptyQ(){
    Queue<T> q1;
    assert(q1.size() == 0);
    const Queue<T> q2;
    assert(q1.size() == 0);

    bool thrown = false;
    try{
        q1.front();
    }
    catch (const Queue<T>::EmptyQueue& e){
        thrown = true;
    }
    assert(thrown == true);
    thrown = false;

    try{
        q1.popFront();
    }
    catch (const Queue<T>::EmptyQueue& e){
        thrown = true;
    }
    assert(thrown == true);
}

void testNEmptyQ(){
    Queue<int> q1;
    assert(q1.size() == 0);
    Queue<int> q2;
    assert(q1.size() == 0);

    for (int i = 0; i < 5; i++){
        q1.pushBack(i);
    }
}

void testQ(){
    testEmptyQ();
    testNEmptyQ();
}


int main(){
    cout << "running tests QUEUE" << endl;
    testQ();
    // testConstQ();
}