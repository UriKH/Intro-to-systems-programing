
#include "TestUtils.h"

void runTest(std::function<bool()> testFunction, std::string testName)
{
	if(!testFunction()){
		std::cout << testName <<" FAILED." << std::endl;
	}
	else {
		std::cout << testName << " SUCCEEDED." << std::endl;
	}
}
