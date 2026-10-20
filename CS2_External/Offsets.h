#pragma once
#include <Windows.h>
#include <cstdint>
#include "Utils/ProcessManager.hpp"

namespace Offset {
    extern DWORD64 EntityList;
    extern DWORD64 Matrix;
    extern DWORD64 LocalPlayerController;
    extern DWORD64 ViewAngle;
    extern DWORD64 LocalPlayerPawn;
    extern DWORD64 ForceJump;
    extern DWORD64 GlobalVars;
    extern DWORD64 Sensitivity;
    extern DWORD64 PlantedC4;
    extern DWORD64 WeaponC4;

    struct GlobalVarOffsets {
        DWORD64 RealTime = 0x0;
        DWORD64 FrameCount = 0x4;
        DWORD64 MaxClients = 0x10;
        DWORD64 TickCount = 0x40;
        DWORD64 IntervalPerTick = 0x44;
        DWORD64 CurrentTime = 0x2C;
        DWORD64 CurrentMapName = 0x180;
    };
    extern GlobalVarOffsets GlobalVar;

    struct EntityOffsets {
        DWORD64 m_iHealth = 0x34C;
        DWORD64 m_iTeamNum = 0x3E7;
        DWORD64 m_bPawnIsAlive = 0x7A0;
        DWORD64 m_iszPlayerName = 0x6FC;
        DWORD64 m_bGlow = 0x0; 
        DWORD64 m_glowColorOverride = 0x0;
        DWORD64 m_hPlayerPawn = 0x6BC;
    };
    extern EntityOffsets Entity;

    struct PawnOffsets {
        DWORD64 m_iHealth = 0x34C;
        DWORD64 m_iTeamNum = 0x3E7;
        DWORD64 m_angEyeAngles = 0x1518;
        DWORD64 m_bSpottedByMask = 0xC;
        DWORD64 m_pWeaponServices = 0x12F0;
        DWORD64 m_iShotsFired = 0x1E9C; 
        DWORD64 m_bSpotted = 0x0; 
        DWORD64 m_vOldOrigin = 0x14A4;
        DWORD64 m_pCameraServices = 0x12F8; 
        DWORD64 m_iFovStart = 0x0; 
        DWORD64 m_fFlags = 0x3F8;
        DWORD64 m_flFlashDuration = 0x1510;
        DWORD64 m_iIDEntIndex = 0x13A4;
        DWORD64 m_flFOVSensitivityAdjust = 0x1520;
    };
    extern PawnOffsets Pawn;

    struct WeaponOffsets {
        DWORD64 m_hActiveWeapon = 0x60;
        DWORD64 m_nSubclassID = 0x0; 
        DWORD64 m_szName = 0x0; 
    };
    extern WeaponOffsets Weapon;

    template <typename T>
    bool GetDataAddressWithOffset(DWORD64 address, DWORD64 offset, T& out) {
        return ReadProcessMemory(ProcessMgr.hProcess, (LPCVOID)(address + offset), &out, sizeof(T), nullptr);
    }

    bool UpdateOffsets();
}
