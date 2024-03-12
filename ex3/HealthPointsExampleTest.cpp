
#include <sstream>

#include "HealthPoints.h"
#include "TestUtils.h"

namespace HealthPointsTests {

static bool checkHealthPointsValues(const HealthPoints& healthPoints, int current, int max)
{
	std::ostringstream expected;
	expected << current << '(' << max << ')';
	std::ostringstream result;
	result << healthPoints;
	return (expected.str() == result.str());
}

bool testInitialization()
{
	bool testResult = true;

	HealthPoints healthPoints1; /* has 100 points out of 100 */
	HealthPoints healthPoints2(150); /* has 150 points out of 150 */
	bool exceptionThrown = false;
	try {
		HealthPoints healthPoints3(-100);
	}
	catch (const HealthPoints::InvalidArgument& e) {
		exceptionThrown = true;
	}

	AGGREGATE_TEST_RESULT(testResult, exceptionThrown);
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints1, 100, 100));
	return testResult;
}

bool testArithmeticOperators()
{
	bool testResult = true;
	HealthPoints healthPoints1; /* has 100 points out of 100 */
	HealthPoints healthPoints2(150); /* has 150 points out of 150 */

	healthPoints1 -= 20; /* now has 80 points out of 100 */
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints1, 80, 100));

	healthPoints1 += 100; /* now has 100 points out of 100 */
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints1, 100, 100));

	healthPoints1 -= 150; /* now has 0 points out of 100 */
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints1, 0, 100));

	healthPoints2 = healthPoints2 - 160; /* now has 0 points out of 150 */
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints2, 0, 150));

	healthPoints2 = 160 + healthPoints1; /* now has 100 out of 100 */
	AGGREGATE_TEST_RESULT(testResult, checkHealthPointsValues(healthPoints2, 100, 100));

	return testResult;

}

bool testComparisonOperators()
{
	bool testResult = true;
	HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
	HealthPoints healthPoints2 = 100; /* has 100 points out of 100 */
	bool comparisonResult;

	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
	AGGREGATE_TEST_RESULT(testResult, comparisonResult);

	healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
	AGGREGATE_TEST_RESULT(testResult, !comparisonResult);

	healthPoints2 -= 50; /* now has 100 points out of 150 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
	AGGREGATE_TEST_RESULT(testResult, comparisonResult);

	comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
	AGGREGATE_TEST_RESULT(testResult, !comparisonResult);

	healthPoints1 -= 50; /* now has 50 points out of 100 */
	comparisonResult = (healthPoints1 < healthPoints2); /* returns true */
	AGGREGATE_TEST_RESULT(testResult, comparisonResult);

	return testResult;
}

bool testOutputOperator()
{
	bool testResult = true;
	std::ostringstream stream;

	HealthPoints healthPoints1 = HealthPoints(100); /* has 100 points out of 100 */
	healthPoints1 -= 50; /* now has 50 points out of 100 */
	stream << healthPoints1; /* stream content is "50(100)" */
	AGGREGATE_TEST_RESULT(testResult, stream.str() == "50(100)");

	HealthPoints healthPoints2 = HealthPoints(150); /* has 1500 points out of 150 */
	healthPoints2 -= 50; /* now has 100 points out of 150 */
	stream << ", " << healthPoints2; /* stream content is "50(100), 100(150)" */
	AGGREGATE_TEST_RESULT(testResult, stream.str() == "50(100), 100(150)");

	return testResult;
}

}
