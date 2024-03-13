#include "queue.h"
#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

void runTest(string msg, void (*func)()){
    cout << msg << endl;
    func();
    cout << "---- finished successfully ----\n" << endl;
}

void testQSize(){
    Queue<int> q;
    assert(q.size() == 0);

    for (int i = 0; i < 5; i++){
        q.pushBack(i);
    }
    assert(q.size() == 5);
}

void testQtop(){
    Queue<int> q;
    assert(q.size() == 0);

    for (int i = 0; i < 5; i++){
        q.pushBack(i);
    }
    assert(q.front() == 0);

    q.popFront();
    assert(q.front() == 1);
}

void testTransform(){
    Queue<int> q;
    for (int i = 0; i < 5; i++){
        q.pushBack(i);
    }

    transform(q, [](int i){return i * 2;});
    int index = 0;
    for (Queue<int>::Iterator it = q.begin(); it != q.end(); ++it){
        assert(*it == index * 2);
        index++;
    }
}

void testReduce(){
    Queue<int> q;
    int sum = 0;
    for (int i = 0; i < 5; i++){
        q.pushBack(i);
        sum += i;
    }

    assert(reduce(q, 0, [](int a, int b){return a + b;}) == sum);
}

void testIterator(){
    Queue<int> q;
    for (int i = 0; i < 5; i++){
        q.pushBack(i);
    }

    // test begin and *
    assert(*q.begin() == 0);

    // test ++
    int index = 0;
    Queue<int>::Iterator it = q.begin();

    for (; it != q.end();){
        assert(*it == index);
        index++;
        ++it;
    }
    assert(index == 5);
}

int main(){
    runTest("testing Queue size", testQSize);
    runTest("testing Queue push front and pop", testQtop);
    runTest("testing Iterator", testIterator);
    runTest("testing transform", testTransform);
    runTest("testing reduce", testReduce);
}