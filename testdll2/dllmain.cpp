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

class UnitTest2 : public Test
{
private:
    TestResult Test1()
    {
        TestResult result;

        result.testName = "Div Test";
        result.testInfo = "Div a two numbers";

        int result_int = 3;

        int a = 9 / 3;

        result.Assert(result_int == a, "Div not working. expected 3, but result = " + std::to_string(a));

        return result;
    }

    TestResult Test2()
    {
        TestResult result;

        result.testName = "Multiply Test";
        result.testInfo = "Multiply a two numbers";

        int result_int = 10;

        int a = 5 * 2;

        result.Assert(result_int == a, "Multiply not working. expected 10, but result = " + std::to_string(a));

        return result;
    }

public:
    UnitTest2()
    {
        name = "UnitTest2";
    }

    std::vector<TestResult>* RunTests() override
    {
        std::vector<TestResult>* result = new std::vector<TestResult>();

        result->push_back(Test1());
        result->push_back(Test2());

        return result;
    }
};

TEST_INTERFACE(UnitTest2)