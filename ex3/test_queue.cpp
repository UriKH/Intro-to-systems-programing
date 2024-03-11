#include "queue.h"
#include <assert.h>

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
    assert(q.front() == 4);

    q.popFront();
    assert(q.front() == 3);
}


int main(){
    testQSize();
    testQtop();
}