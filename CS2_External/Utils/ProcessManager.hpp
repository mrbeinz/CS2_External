#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

class ProcessManager
{
public:
    HANDLE hProcess = nullptr;
    DWORD ProcessID = 0;
    DWORD64 BaseAddress = 0;
    DWORD64 ModuleSize = 0;

    // Original methods that VTableSearch.cpp relies on
    DWORD64 GetModuleBase(const std::string& ModuleName);
    DWORD64 GetModuleSize(const std::string& ModuleName);
    
    DWORD64 FindQWordInSections(DWORD64 Address, DWORD64 Value, DWORD64 Size);
    DWORD64 FindVTable(DWORD64 Address, DWORD64 Size);
    DWORD64 FindVTableInstance(DWORD64 Address, DWORD64 VTable);

    // Helper to convert string without ATL
    std::wstring StringToWString(const std::string& str)
    {
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }

    template <typename T>
    T ReadMemory(DWORD64 Address)
    {
        T Buffer{};
        ReadProcessMemory(hProcess, (LPCVOID)Address, &Buffer, sizeof(T), nullptr);
        return Buffer;
    }

    template <typename T>
    bool ReadMemory(DWORD64 Address, T& Out)
    {
        return ReadProcessMemory(hProcess, (LPCVOID)Address, &Out, sizeof(T), nullptr);
    }

    bool ReadMemory(DWORD64 Address, void* Buffer, size_t Size)
    {
        return ReadProcessMemory(hProcess, (LPCVOID)Address, Buffer, Size, nullptr);
    }

    template <typename T>
    bool WriteMemory(DWORD64 Address, const T& Value)
    {
        return WriteProcessMemory(hProcess, (LPVOID)Address, &Value, sizeof(T), nullptr);
    }

    bool WriteMemory(DWORD64 Address, const void* Buffer, size_t Size)
    {
        return WriteProcessMemory(hProcess, (LPVOID)Address, Buffer, Size, nullptr);
    }
};

// Global instance used everywhere
extern ProcessManager ProcessMgr;
