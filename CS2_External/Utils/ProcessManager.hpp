#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <cstdint>

enum StatusCode { SUCCEED = 0, FAILED = 1 };

class ProcessManager {
public:
    HANDLE hProcess = nullptr;
    DWORD ProcessID = 0;

    std::wstring StringToWString(const std::string& str) {
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }

    StatusCode Attach(const std::string& processName) {
        std::wstring wProcessName = StringToWString(processName);
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) return FAILED;
        PROCESSENTRY32W pe32{ sizeof(PROCESSENTRY32W) };
        if (Process32FirstW(hSnapshot, &pe32)) {
            do {
                if (wProcessName == pe32.szExeFile) {
                    ProcessID = pe32.th32ProcessID;
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
                    CloseHandle(hSnapshot);
                    return (hProcess != nullptr) ? SUCCEED : FAILED;
                }
            } while (Process32NextW(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
        return FAILED;
    }

    DWORD64 GetProcessModuleHandle(const std::string& moduleName) {
        std::wstring wModuleName = StringToWString(moduleName);
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
        if (hSnapshot == INVALID_HANDLE_VALUE) return 0;
        MODULEENTRY32W me32{ sizeof(MODULEENTRY32W) };
        if (Module32FirstW(hSnapshot, &me32)) {
            do {
                if (wModuleName == me32.szModule) {
                    DWORD64 base = (DWORD64)me32.modBaseAddr;
                    CloseHandle(hSnapshot);
                    return base;
                }
            } while (Module32NextW(hSnapshot, &me32));
        }
        CloseHandle(hSnapshot);
        return 0;
    }

    // Declarations for VTableSearch.cpp
    DWORD64 GetModuleSize(DWORD64 Address);
    std::vector<DWORD64> SearchMemory(const std::string& Signature, DWORD64 Start, DWORD64 Size, int Flags);
    DWORD64 FindQWordInSections(DWORD64 Address, DWORD64 Value, DWORD Size);
    DWORD64 FindVTable(DWORD64 Address, const std::string& VTableName);
    DWORD64 FindVTableInstance(DWORD64 Address, const std::string& VTableName);
    
    // Fixed TraceAddress for TriggerBot.cpp (accepts vector)
    DWORD64 TraceAddress(DWORD64 Address, std::vector<DWORD> Offsets) {
        DWORD64 current = Address;
        for (DWORD offset : Offsets) {
            if (!ReadProcessMemory(hProcess, (LPCVOID)current, &current, sizeof(current), nullptr)) return 0;
            current += offset;
        }
        return current;
    }

    template <typename T>
    T ReadMemory(DWORD64 address) {
        T buffer{};
        ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), nullptr);
        return buffer;
    }

    template <typename T>
    bool ReadMemory(DWORD64 address, T& out) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, &out, sizeof(T), nullptr);
    }

    // Fixed MemorySearch.cpp / VTableSearch.cpp overload
    template <typename T>
    bool ReadMemory(DWORD64 address, T& out, size_t size) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, &out, size, nullptr);
    }

    bool ReadMemory(DWORD64 address, void* buffer, size_t size) {
        return ReadProcessMemory(hProcess, (LPCVOID)address, buffer, size, nullptr);
    }

    template <typename T>
    bool WriteMemory(DWORD64 address, const T& value) {
        return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
    }

    bool WriteMemory(DWORD64 address, void* buffer, size_t size) {
        return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, nullptr);
    }
};

inline ProcessManager ProcessMgr;
