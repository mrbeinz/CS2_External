#include "ProcessManager.hpp"
#include <vector>
#include <psapi.h>

ProcessManager ProcessMgr;

DWORD64 ProcessManager::GetModuleBase(const std::string& ModuleName)
{
    std::wstring wModuleName = StringToWString(ModuleName);
    DWORD64 Base = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W ModuleEntry{ sizeof(MODULEENTRY32W) };
        if (Module32FirstW(hSnapshot, &ModuleEntry))
        {
            do
            {
                if (wModuleName == ModuleEntry.szModule)
                {
                    Base = (DWORD64)ModuleEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnapshot, &ModuleEntry));
        }
        CloseHandle(hSnapshot);
    }
    return Base;
}

DWORD64 ProcessManager::GetModuleSize(const std::string& ModuleName)
{
    std::wstring wModuleName = StringToWString(ModuleName);
    DWORD64 Size = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W ModuleEntry{ sizeof(MODULEENTRY32W) };
        if (Module32FirstW(hSnapshot, &ModuleEntry))
        {
            do
            {
                if (wModuleName == ModuleEntry.szModule)
                {
                    Size = ModuleEntry.modBaseSize;
                    break;
                }
            } while (Module32NextW(hSnapshot, &ModuleEntry));
        }
        CloseHandle(hSnapshot);
    }
    return Size;
}

// Stub implementations for VTable Search (These are complex memory scanners)
// Returning 0 will bypass the dynamic find and use the hardcoded offsets if implemented that way.
DWORD64 ProcessManager::FindQWordInSections(DWORD64 Address, DWORD64 Value, DWORD64 Size) { return 0; }
DWORD64 ProcessManager::FindVTable(DWORD64 Address, DWORD64 Size) { return 0; }
DWORD64 ProcessManager::FindVTableInstance(DWORD64 Address, DWORD64 VTable) { return 0; }
