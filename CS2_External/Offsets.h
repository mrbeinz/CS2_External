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
    extern DWORD64 GlobalVars; // Plural (Base Address)
    extern DWORD64 Sensitivity_Value;
    extern DWORD64 PlantedC4;
    extern DWORD64 WeaponC4;

    // Struct for GlobalVar sub-offsets
    struct GlobalVarOffsets {
        DWORD64 RealTime = 0x0;
        DWORD64 FrameCount = 0x4;
        DWORD64 MaxClients = 0x10;
        DWORD64 TickCount = 0x40;
        DWORD64 IntervalPerTick = 0x44;
        DWORD64 CurrentTime = 0x2C;
        DWORD64 CurrentMapName = 0x180;
    };
    extern GlobalVarOffsets GlobalVar; // Singular struct

    // Struct for Pawn offsets
    struct PawnOffsets {
        DWORD64 m_iHealth = 0x34C;
        DWORD64 m_iTeamNum = 0x3E7;
        DWORD64 m_flFlashDuration = 0x1510;
        DWORD64 m_fFlags = 0x3F8;
        DWORD64 m_iIDEntIndex = 0x13A4; 
        DWORD64 m_flFOVSensitivityAdjust = 0x1520; 
    };
    extern PawnOffsets Pawn;

    // 3-argument template for writing to a reference
    template <typename T>
    bool GetDataAddressWithOffset(DWORD64 address, DWORD64 offset, T& out) {
        return ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &out, sizeof(T), nullptr);
    }

    // 2-argument template for returning a value (kept for backwards compatibility)
    template <typename T>
    T GetDataAddressWithOffset(DWORD64 address, DWORD64 offset) {
        T result{};
        ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &result, sizeof(T), nullptr);
        return result;
    }

    bool UpdateOffsets();
}
