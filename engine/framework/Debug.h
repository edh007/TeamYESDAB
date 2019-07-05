#pragma once

#include <Windows.h>
#include <stdio.h>

//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#endif // _DEBUG

#ifdef _DEBUG
#define DEBUG_CREATE_CONSOLE() \
	AllocConsole();\
	FILE* pFile;\
	freopen_s(&pFile, "CONOUT$", "w", stdout);\
	freopen_s(&pFile, "CONOUT$", "w", stderr);
#define DEBUG_DESTROY_CONSOLE() \
	freeConsole();
// https://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing
#define DEBUG_PRINT(cond, ...) do{fprintf(stdout, "%s:%d:%s(): "#cond"\n", __FILE__,__LINE__,__func__, __VA_ARGS__);}while(0)
#define DEBUG_ASSERT(cond, exp, ...) assert(!(cond) && (#exp));
#else // _DEBUG
#define DEBUG_CREATE_CONSOLE() 
#define DEBUG_DESTROY_CONSOLE()
#define DEBUG_PRINT(cond, ...)
#define DEBUG_ASSERT(cond, exp, ...)
#endif // _DEBUG

