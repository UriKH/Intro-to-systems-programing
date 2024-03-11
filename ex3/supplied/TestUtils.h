
#pragma once

#include <functional>
#include <iostream>

#define AGGREGATE_TEST_RESULT(res, cond) ((res) = ((res) && (cond)))

void runTest(std::function<bool()> testFunction, std::string testName);
