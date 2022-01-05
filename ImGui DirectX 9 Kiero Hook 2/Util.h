// Copyright [2021] <tiansongyu>

#ifndef IMGUI_DIRECTX_9_KIERO_HOOK_2_UTIL_H_
#define IMGUI_DIRECTX_9_KIERO_HOOK_2_UTIL_H_

#include <TlHelp32.h>
#include <Windows.h>
#include <stdarg.h>
#include <tchar.h>
namespace UTIL {
DWORD_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR* szModuleName);
// ex:
// get_health(4,0x400000,0x1880C4,0,0x408)
int* getOffsetPointer(int n, ...);
}  // namespace UTIL
#endif  // IMGUI_DIRECTX_9_KIERO_HOOK_2_UTIL_H_
