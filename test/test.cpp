#include <iostream>
#include <windows.h>
#include <vector>
#include <locale>
#include <codecvt>

#include "TestAPI.h"

std::string wstringTostring(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}

struct ModuleInfo
{
	HMODULE handle;
	std::string name;
};

int main()
{
	setlocale(LC_ALL, "RU");

	WIN32_FIND_DATAW findData;

	std::wstring path = L".\\tests\\";
	std::wstring filter = path + L"*.dll";

	HANDLE fileHandle = FindFirstFileW(filter.c_str(), &findData);

	if (fileHandle == (void*)ERROR_INVALID_HANDLE)
	{
		std::wcout << "No modules for Test" << std::endl;
		return 0;
	}

	std::vector<Test*> testModules;

	std::cout << "Detected Modules:\n";

	do
	{
		std::wstring moduleName = findData.cFileName;
		std::wstring modulePath = path + moduleName;

		HMODULE mod = LoadLibraryW(modulePath.c_str());

		if (!mod)
		{
			std::wstring error = L"Error loading module ";
			error += moduleName;
			std::wcout << error << std::endl;

			continue;
		}

		InstanceFunc func = (InstanceFunc)GetProcAddress(mod, "GetTestInstance");

		if (!func)
		{
			std::wcout << L"Module " + path + moduleName + L"\t[ERROR]\nERROR: Module not constains GetTestInstance function. Maybe you forgot add TEST_INTERFACE macros in module File?\n";
		}
		else
		{
			std::wcout << L"Module " + path +  moduleName << L"\t[OK]" << std::endl;

			testModules.push_back(func());
		}
	} while (FindNextFileW(fileHandle, &findData));

	std::cout << "------------------" << std::endl;

	for (Test* test : testModules)
	{
		std::cout << "Test module: " + test->GetName() << std::endl;

		std::vector<TestResult>* results = test->RunTests();

		for (TestResult result : *results)
		{
			if (result.isSuccess)
			{
				std::cout << "[+] ";
			}
			else
			{
				std::cout << "[-] ";
			}

			if (!result.isSuccess)
			{
				std::cout << result.testName + "\t FAILED" << std::endl;

				std::cout << " | Test Info: " + result.testInfo << std::endl;

				std::cout << " | Error message:\n | " + result.message << std::endl;
			}
			else
			{
				std::cout << result.testName << std::endl;
			}
		}

		std::cout << "------------------" << std::endl;
	}
}
