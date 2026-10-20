#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

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

    bool Attach(const std::string& processName) {
        std::wstring wProcessName = StringToWString(processName);
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) return false;
        PROCESSENTRY32W pe32{ sizeof(PROCESSENTRY32W) };
        if (Process32FirstW(hSnapshot, &pe32)) {
            do {
                if (wProcessName == pe32.szExeFile) {
                    ProcessID = pe32.th32ProcessID;
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
                    CloseHandle(hSnapshot);
                    return true;
                }
            } while (Process32NextW(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
        return false;
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

    // Declarations only. Let VTableSearch.cpp / MemorySearch.cpp define them.
    DWORD64 GetModuleSize(DWORD64 address);
    DWORD64 TraceAddress(DWORD64 address, DWORD64 size);
    std::vector<DWORD64> SearchMemory(const std::string& signature, DWORD64 startAddress, DWORD64 size, int flags);
    DWORD64 FindQWordInSections(DWORD64 address, DWORD64 value, DWORD size);
    DWORD64 FindVTable(DWORD64 address, const std::string& name);
    DWORD64 FindVTableInstance(DWORD64 address, const std::string& name);

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
