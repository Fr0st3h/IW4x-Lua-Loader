#include "logger.hpp"

#include <stdio.h>
#include <stdarg.h>

void scol(DWORD col)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

namespace Logger
{

	void debugPrint(const char* string) {
		std::ofstream fileOUT("codlua.log", std::ios::app);

		const char* test = "[CODLUA] ";

		char result[100];   // array to hold the result.

		strcpy_s(result, test); // copy string one into the result.
		strcat_s(result, string); // append string two to the result.

		fileOUT << result << std::endl;

		fileOUT.close();
	}

	void debugPrint(char* string) {
		std::ofstream fileOUT("codlua.log", std::ios::app);

		const char* test = "[CODLUA] ";

		char result[250];   // array to hold the result.

		strcpy_s(result, test); // copy string one into the result.
		strcat_s(result, string); // append string two to the result.

		fileOUT << result << std::endl;

		fileOUT.close();
	}

	void append(kLogType logType, std::string text, ...)
	{
		va_list argptr;
		va_start(argptr, text);

		std::string col, tag;

		switch (logType)
		{
		case kLogType::NORMAL:
			break;
		case kLogType::ERROR:
			scol(FOREGROUND_RED);
			printf("[");
			scol(FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("!");
			scol(FOREGROUND_RED);
			printf("] ");
			scol(FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case kLogType::WARNING:
			break;
		case kLogType::SUCCESS:
			scol(FOREGROUND_GREEN);
			printf("[");
			scol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("+");
			scol(FOREGROUND_GREEN);
			printf("] ");
			scol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		default:
			break;
		}

		std::string out = tag + col + text;

		vprintf(out.c_str(), argptr);
		scol(0x07);

		va_end(argptr);
	}
}