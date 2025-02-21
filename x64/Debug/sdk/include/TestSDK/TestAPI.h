#pragma once
#include <string>
#include <vector>

struct TestResult
{
	bool isSuccess;

	std::string testName;
	std::string testInfo;
	std::string message;

	TestResult()
	{
		isSuccess = true;
	}

	void Assert(bool result, std::string message)
	{
		isSuccess = result;

		if (!result)
		{
			this->message = message;
		}
	}
};

/// <summary>
/// Класс Теста. Для реализации своего теста необходимо переопределить метод RunTests. Рекомендуется писать отдельные функции, заполняющие TestResult
/// После чего использовать их в RunTests. После класса необходимо написать TEST_INTERFACE, указав ваш класс. В конструкторе класса можно установит имя
/// вашему тесту. Всего в DLL может быть не больше одного теста
/// </summary>
class Test
{
protected:
	std::string name;

public:
	Test()
	{
		name = "DefaultTest";
	}

	virtual std::vector<TestResult>* RunTests() = 0;

	inline std::string GetName() 
	{
		return name;
	}

	virtual ~Test() = default;
};

#ifndef _TEST
#define PLUGIN_EXPORT __declspec(dllexport)
#else
#define PLUGIN_EXPORT
#endif

//
//extern "C"
//{
//	PLUGIN_EXPORT void* GetTestInstance();
//}

#define TEST_INTERFACE(ClassName) extern "C"\
{ \
	__declspec(dllexport) void* GetTestInstance() \
	{ \
		return (void*)new ClassName(); \
	} \
} 

using InstanceFunc = Test * (__cdecl*)(void);