#include "queue.h"
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

int main(){
    Queue<int> l;
    for (int i = 0; i < 5; i++){
        l.pushBack(i);
    }
    assert(l.size() == 5);
    for (int i = 0; i < 5; i++){
        l.popFront();
    }
    assert(l.size() == 0);
    for (int i = 0; i < 5; i++){
        l.pushBack(i);
    }

    // copty ctor
    Queue<int> q = l;
    assert(q.size() == 5);
    assert(&(q.front()) != &(l.front()));

    // operator =
    Queue<int> q2;
    q2 = l;
    assert(q.size() == 5);
    assert(&(q.front()) != &(l.front()));

    cout << "test finished successfully" << endl;
}