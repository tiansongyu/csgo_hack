// Copyright [2021] <tiansongyu>

#include "Util.h"
int* UTIL::getOffsetPointer(int n, ...) {
  va_list vl;
  va_start(vl, n);
  int base_address = va_arg(vl, int);
  int ret_address = base_address + va_arg(vl, int);
  for (int i = 2; i < n; i++) {
    ret_address = *(static_cast<int*>ret_address) + va_arg(vl, int);
  }
  return static_cast<int*>(ret_address);
}
DWORD_PTR UTIL::dwGetModuleBaseAddress(DWORD dwProcID, TCHAR* szModuleName) {
  DWORD_PTR dwModuleBaseAddress = 0;
  HANDLE hSnapshot = CreateToolhelp32Snapshot(
      TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
  if (hSnapshot != INVALID_HANDLE_VALUE) {
    MODULEENTRY32 ModuleEntry32;
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &ModuleEntry32)) {
      do {
        if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0) {
          dwModuleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
          break;
        }
      } while (Module32Next(hSnapshot, &ModuleEntry32));
    }
    CloseHandle(hSnapshot);
  }
  return dwModuleBaseAddress;
}
