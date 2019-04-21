#ifdef KD_TESTS_h
#define KD_TESTS_h

#include "ReadableInterface.hpp"
#include "WritableInterface.hpp"
#include "KDTestSensorReader.hpp"
#include "KDConstexprTest.hpp"

class KDTests
{
  public:
    static void callKDConstexprTest()
    {
        constexpr KDConstexprTest constexprTest = KDConstexprTest(10);
        static_assert(constexprTest.Test() == 10, "error");
        constexprTest.read();
    }
    static void callSinTableTest()
    {
        unsigned long ms360 = millis() % 360;
        KDDebugUtility::printInt(ms360);
        KDDebugUtility::printInt(sin(ms360 * KDMath::deg2Rad) * 10000);
        KDDebugUtility::printInt(KDMath::sinByTable(ms360) * 10000);
        KDDebugUtility::printInt(abs(KDMath::sinByTable(ms360) - sin(ms360 * KDMath::deg2Rad)) < 0.001);
        KDDebugUtility::printInt(0 == 0);
    }
    static void callKdConstexprTest()
    {
        unsigned long ms360 = millis() % 360;
        KDDebugUtility::printInt(ms360);
        KDDebugUtility::printInt(cos(ms360 * KDMath::deg2Rad) * 10000);
        KDDebugUtility::printInt(KDMath::cosByTable(ms360) * 10000);
        KDDebugUtility::printInt(abs(KDMath::cosByTable(ms360) - cos(ms360 * KDMath::deg2Rad)) < 0.001);
        KDDebugUtility::printInt(0 == 0);
    }
    static void callReadableInterfaceTest()
    {
        Reader<KDTestSensorReader> testReader = Reader<KDTestSensorReader>(&KDTestSensorReader(10));
        testReader.read();
    }
};

#endif