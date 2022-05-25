#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#ifdef ERROR
#undef ERROR
#endif

namespace Logger
{


	const enum kLogType
	{
		NORMAL,
		WARNING,
		ERROR,
		SUCCESS
	};

	void append(kLogType logType, std::string text, ...);
	void debugPrint(char* string);
	void debugPrint(const char* string);
	class Debug {
	public:
		void debugPrint(const char* string) {
			std::ofstream fileOUT("codlua.log", std::ios::app);

			const char* test = "[CODLUA] ";

			char result[100];   // array to hold the result.

			strcpy_s(result, test); // copy string one into the result.
			strcat_s(result, string); // append string two to the result.

			fileOUT << result << std::endl;

			fileOUT.close();
		}
	};
}