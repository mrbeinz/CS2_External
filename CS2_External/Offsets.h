#pragma once
#include <cstdint>
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset {
    // Core Pointers
    extern DWORD64 EntityList;
    extern DWORD64 Matrix;
    extern DWORD64 LocalPlayerController;
    extern DWORD64 ViewAngle;
    extern DWORD64 LocalPlayerPawn;
    extern DWORD64 ForceJump;
    extern DWORD64 GlobalVar;
    extern DWORD64 Sensitivity_Value;
    extern DWORD64 PlantedC4;
    extern DWORD64 WeaponC4;

    // Pawn Structure Offsets (used by TriggerBot/AntiFlash)
    namespace Pawn {
        extern DWORD64 m_iHealth;
        extern DWORD64 m_iTeamNum;
        extern DWORD64 m_flFlashDuration;
    }

    template <typename T>
    T GetDataAddressWithOffset(DWORD64 address, DWORD64 offset) {
        T result{};
        ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &result, sizeof(T), nullptr);
        return result;
    }

    bool UpdateOffsets();
}
