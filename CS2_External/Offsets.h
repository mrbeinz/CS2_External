#pragma once
#include <Windows.h>
#include <cstdint>
#include "Utils/ProcessManager.hpp"

namespace Offset {
    extern DWORD64 Entity;
    extern DWORD64 Matrix;
    extern DWORD64 LocalPlayerController;
    extern DWORD64 ViewAngle;
    extern DWORD64 LocalPlayerPawn;
    extern DWORD64 ForceJump;
    extern DWORD64 GlobalVar; // Singular
    extern DWORD64 Sensitivity_Value;
    extern DWORD64 PlantedC4;
    extern DWORD64 WeaponC4;

    namespace Pawn {
        constexpr DWORD64 m_iHealth = 0x34C;
        constexpr DWORD64 m_iTeamNum = 0x3E7;
        constexpr DWORD64 m_flFlashDuration = 0x1510;
        constexpr DWORD64 m_fFlags = 0x3F8;
        constexpr DWORD64 m_iIDEntIndex = 0x13A4; // Added missing
        constexpr DWORD64 m_flFOVSensitivityAdjust = 0x1520; // Added missing
    }

    template <typename T>
    T GetDataAddressWithOffset(DWORD64 address, DWORD64 offset) {
        T result{};
        ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &result, sizeof(T), nullptr);
        return result;
    }

    bool UpdateOffsets();
}
