// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "TestAPI.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

class UnitTest1 : public Test
{
private:
    TestResult Test1()
    {
        TestResult result;

        result.testName = "Plus Test";
        result.testInfo = "plus a two numbers";

        int result_int = 3;

        int a = 1 + 2;

        result.Assert(result_int == a, "plus not working. expected 5, but result = " + std::to_string(a));

        return result;
    }

    TestResult Test2()
    {
        TestResult result;

        result.testName = "Minus Test";
        result.testInfo = "Minus a two numbers";

        int result_int = 3;

        int a = 5 - 3;

        result.Assert(result_int == a, "minus not working. expected 3, but result = " + std::to_string(a));

        return result;
    }

public:
    UnitTest1()
    {
        name = "UnitTest1";
    }

    std::vector<TestResult>* RunTests() override
    {
        std::vector<TestResult>* result = new std::vector<TestResult>();

        result->push_back(Test1());
        result->push_back(Test2());

        return result;
    }
};

TEST_INTERFACE(UnitTest1)