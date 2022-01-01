#ifndef Util__
#define Util__

#include <stdarg.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <Windows.h>
namespace UTIL
{
	DWORD_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR* szModuleName);
	// ex:
	// get_health(4,0x400000,0x1880C4,0,0x408)
	// 用于获取offset指针
	int* getOffsetPointer(int n, ...);
}
#endif // !Util__
