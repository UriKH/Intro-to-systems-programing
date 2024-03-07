
#include <iostream>

#include "Queue.h"
#include "TestUtils.h"

static bool isEven(int n)
{
	return (n % 2) == 0;
}

static int addThree(int n)
{
	return n + 3;
}

static int add(int a, int b)
{
	return a + b;
}

static int multiply(int a, int b)
{
	return a * b;
}

namespace QueueTests {

bool testQueueMethods()
{
	bool testResult = true;

	Queue<int> queue1;
	queue1.pushBack(1);
	queue1.pushBack(2);
	int front1 = queue1.front();
	AGGREGATE_TEST_RESULT(testResult, front1 == 1);

	queue1.front() = 3;
	front1 = queue1.front();
	AGGREGATE_TEST_RESULT(testResult, front1 == 3);

	queue1.popFront();
	front1 = queue1.front();
	AGGREGATE_TEST_RESULT(testResult, front1 == 2);

	int size1 = queue1.size();
	AGGREGATE_TEST_RESULT(testResult, size1 == 1);

	return testResult;
}

bool testModuleFunctions()
{
	bool testResult = true;

	Queue<int> queue3;
	for (int i = 1; i <= 10; i++) {
		queue3.pushBack(i);
	}
	Queue<int> queue4 = filter(queue3, isEven);
	for (int i = 2; i <= 10; i+=2) {
		int front4 = queue4.front();
		AGGREGATE_TEST_RESULT(testResult, front4 == i);
		queue4.popFront();
	}


	Queue<int> queue5;
	for (int i = 1; i <= 5; i++) {
		queue5.pushBack(i);
	}
	transform(queue5, addThree);
	for (int i = 1; i <= 5; i++) {
		int front5 = queue5.front();
		AGGREGATE_TEST_RESULT(testResult, front5 == i + 3);
		queue5.popFront();
	}

	Queue<int> queue6;
	for (int i = 1; i <= 5; i++) {
		queue6.pushBack(i);
	}
	int sum = reduce(queue6, 0, add);
	int mul = reduce(queue6, 1, multiply); /* mul now equals 120 */
	AGGREGATE_TEST_RESULT(testResult,(sum == 15));
	AGGREGATE_TEST_RESULT(testResult,(mul == 120));


	return testResult;
}

bool testExceptions()
{
	bool testResult = true;

	bool exceptionThrown = false;
	Queue<int> queue6;
	try {
		queue6.front() = 5;
	}
	catch (const Queue<int>::EmptyQueue& e) {
		exceptionThrown = true;
	}
	AGGREGATE_TEST_RESULT(testResult, exceptionThrown);

	exceptionThrown = false;
	Queue<int>::Iterator endIterator = queue6.end();
	try {
		++endIterator;
	}
	catch (const Queue<int>::Iterator::InvalidOperation& e) {
		exceptionThrown = true;
	}
	AGGREGATE_TEST_RESULT(testResult, exceptionThrown);

	return testResult;
}

bool testConstQueue()
{
	bool testResult = true;

	Queue<int> queue5;
	for (int i = 1; i <= 5; i++) {
		queue5.pushBack(42);
	}
	const Queue<int> constQueue = queue5;
	for (Queue<int>::ConstIterator i = constQueue.begin(); i != constQueue.end(); ++i) {
		AGGREGATE_TEST_RESULT(testResult, (*i == 42));
	}

	bool exceptionThrown = false;
	Queue<int>::ConstIterator endConstIterator = constQueue.end();
	try {
		++endConstIterator;
	}
	catch (const Queue<int>::ConstIterator::InvalidOperation& e) {
		exceptionThrown = true;
	}
	AGGREGATE_TEST_RESULT(testResult, exceptionThrown);

	return testResult;
}

}
