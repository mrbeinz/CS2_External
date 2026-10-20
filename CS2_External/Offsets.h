#pragma once
#include <cstdint>
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset {
    extern DWORD64 Entity;
    extern DWORD64 Matrix;
    extern DWORD64 LocalPlayerController;
    extern DWORD64 ViewAngle;
    extern DWORD64 LocalPlayerPawn;
    extern DWORD64 ForceJump;
    extern DWORD64 GlobalVars;
    extern DWORD64 Sensitivity;
    extern DWORD64 PlantedC4;
    extern DWORD64 WeaponC4;

    // Pawn must be a struct instance, not a namespace
    struct PawnOffsets {
        DWORD64 m_iHealth = 0x34C;
        DWORD64 m_iTeamNum = 0x3E7;
        DWORD64 m_flFlashDuration = 0x1510;
        DWORD64 m_fFlags = 0x3F8;
    };
    extern PawnOffsets Pawn;

    template <typename T>
    T GetDataAddressWithOffset(DWORD64 address, DWORD64 offset) {
        T result{};
        ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &result, sizeof(T), nullptr);
        return result;
    }

    bool UpdateOffsets();
}
