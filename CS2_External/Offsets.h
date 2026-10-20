#pragma once
#include <cstdint>
#include <Windows.h>

namespace Offset {
    extern DWORD64 dwEntityList;
    extern DWORD64 dwLocalPlayerController;
    extern DWORD64 dwViewMatrix;
    extern DWORD64 dwViewAngles;
    extern DWORD64 dwGlobalVars;
    extern DWORD64 dwPlantedC4;
    extern DWORD64 dwWeaponC4;
    
    bool UpdateOffsets();
}
