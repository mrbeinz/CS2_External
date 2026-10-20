#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

inline HANDLE hProcess = nullptr;

class ProcessManager
{
public:
    static DWORD GetProcessId(const std::string& ProcessName)
    {
        std::wstring wProcessName(ProcessName.begin(), ProcessName.end());
        DWORD ProcessId = 0;
        HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (Snapshot != INVALID_HANDLE_VALUE)
        {
            PROCESSENTRY32W ProcessEntry{ sizeof(PROCESSENTRY32W) };
            if (Process32FirstW(Snapshot, &ProcessEntry))
            {
                do
                {
                    if (wProcessName == ProcessEntry.szExeFile)
                    {
                        ProcessId = ProcessEntry.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(Snapshot, &ProcessEntry));
            }
            CloseHandle(Snapshot);
        }
        return ProcessId;
    }

    static DWORD64 GetModuleBase(DWORD ProcessId, const std::string& ModuleName)
    {
        std::wstring wModuleName(ModuleName.begin(), ModuleName.end());
        DWORD64 BaseAddress = 0;
        HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessId);
        if (Snapshot != INVALID_HANDLE_VALUE)
        {
            MODULEENTRY32W ModuleEntry{ sizeof(MODULEENTRY32W) };
            if (Module32FirstW(Snapshot, &ModuleEntry))
            {
                do
                {
                    if (wModuleName == ModuleEntry.szModule)
                    {
                        BaseAddress = (DWORD64)ModuleEntry.modBaseAddr;
                        break;
                    }
                } while (Module32NextW(Snapshot, &ModuleEntry));
            }
            CloseHandle(Snapshot);
        }
        return BaseAddress;
    }

    template <typename T>
    static T ReadMemory(DWORD64 Address)
    {
        T Buffer{};
        ReadProcessMemory(hProcess, (LPCVOID)Address, &Buffer, sizeof(T), nullptr);
        return Buffer;
    }

    template <typename T>
    static bool ReadMemory(DWORD64 Address, T& Out)
    {
        return ReadProcessMemory(hProcess, (LPCVOID)Address, &Out, sizeof(T), nullptr);
    }

    static bool ReadMemory(DWORD64 Address, void* Buffer, size_t Size)
    {
        return ReadProcessMemory(hProcess, (LPCVOID)Address, Buffer, Size, nullptr);
    }

    template <typename T>
    static bool WriteMemory(DWORD64 Address, const T& Value)
    {
        return WriteProcessMemory(hProcess, (LPVOID)Address, &Value, sizeof(T), nullptr);
    }

    static bool WriteMemory(DWORD64 Address, const void* Buffer, size_t Size)
    {
        return WriteProcessMemory(hProcess, (LPVOID)Address, Buffer, Size, nullptr);
    }
};
