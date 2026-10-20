#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

enum StatusCode
{
    SUCCEED = 0,
    FAILED = 1,
};

class ProcessManager {
public:
    static inline HANDLE hProcess = nullptr;
    static inline DWORD ProcessID = 0;
    static inline DWORD64 BaseAddress = 0;
    static inline DWORD64 ModuleSize = 0;

    StatusCode Attach(const std::string& ProcessName) {
        std::wstring wProcessName(ProcessName.begin(), ProcessName.end());
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) return FAILED;
        PROCESSENTRY32W ProcessEntry{ sizeof(PROCESSENTRY32W) };
        if (Process32FirstW(hSnapshot, &ProcessEntry)) {
            do {
                if (wProcessName == ProcessEntry.szExeFile) {
                    ProcessID = ProcessEntry.th32ProcessID;
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
                    CloseHandle(hSnapshot);
                    return SUCCEED;
                }
            } while (Process32NextW(hSnapshot, &ProcessEntry));
        }
        CloseHandle(hSnapshot);
        return FAILED;
    }

    DWORD64 GetProcessModuleHandle(const std::string& ModuleName) {
        std::wstring wModuleName(ModuleName.begin(), ModuleName.end());
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
        if (hSnapshot == INVALID_HANDLE_VALUE) return 0;
        MODULEENTRY32W ModuleEntry{ sizeof(MODULEENTRY32W) };
        if (Module32FirstW(hSnapshot, &ModuleEntry)) {
            do {
                if (wModuleName == ModuleEntry.szModule) {
                    DWORD64 base = (DWORD64)ModuleEntry.modBaseAddr;
                    CloseHandle(hSnapshot);
                    return base;
                }
            } while (Module32NextW(hSnapshot, &ModuleEntry));
        }
        CloseHandle(hSnapshot);
        return 0;
    }

    DWORD64 GetModuleSize(const std::string& ModuleName) {
        std::wstring wModuleName(ModuleName.begin(), ModuleName.end());
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
        if (hSnapshot == INVALID_HANDLE_VALUE) return 0;
        MODULEENTRY32W ModuleEntry{ sizeof(MODULEENTRY32W) };
        if (Module32FirstW(hSnapshot, &ModuleEntry)) {
            do {
                if (wModuleName == ModuleEntry.szModule) {
                    DWORD64 size = ModuleEntry.modBaseSize;
                    CloseHandle(hSnapshot);
                    return size;
                }
            } while (Module32NextW(hSnapshot, &ModuleEntry));
        }
        CloseHandle(hSnapshot);
        return 0;
    }
    
    DWORD64 GetModuleSize(DWORD64 Address) { return ModuleSize; }

    static DWORD64 FindQWordInSections(DWORD64 address, DWORD64 value, DWORD64 size) { return 0; }
    static DWORD64 FindVTable(DWORD64 address, const std::string& name) { return 0; }
    static DWORD64 FindVTableInstance(DWORD64 address, const std::string& name) { return 0; }
    static DWORD64 SearchMemory(const std::string& signature, DWORD64 startAddress, DWORD64 size) { return 0; }
    static DWORD64 TraceAddress(DWORD64 address) { return 0; }

    template <typename T>
    bool ReadMemory(DWORD64 address, T& out) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, &out, sizeof(T), nullptr);
    }

    template <typename T>
    bool ReadMemory(DWORD64 address, T& out, size_t size) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, &out, size, nullptr);
    }

    template <typename T>
    T ReadMemory(DWORD64 address) {
        T out{};
        ReadProcessMemory(hProcess, (LPCVOID)address, &out, sizeof(T), nullptr);
        return out;
    }

    bool ReadMemory(DWORD64 address, void* buffer, size_t size) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, buffer, size, nullptr);
    }

    template <typename T>
    bool WriteMemory(DWORD64 address, T value) {
        return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
    }

    bool WriteMemory(DWORD64 address, void* buffer, size_t size) {
        return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, nullptr);
    }
};

inline ProcessManager ProcessMgr;
