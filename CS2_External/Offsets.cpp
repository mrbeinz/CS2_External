#include "Offsets.h"
#include "Game.h"
#include "Utils/ProcessManager.hpp"

namespace Offset {
    // Hardcoded from your dumper to bypass pattern scanning failures
    DWORD64 dwEntityList = 0x271A908;
    DWORD64 dwLocalPlayerController = 0x253CB78;
    DWORD64 dwViewMatrix = 0x256B020;
    DWORD64 dwViewAngles = 0x257BCC8;
    DWORD64 dwGlobalVars = 0x2230090;
    DWORD64 dwPlantedC4 = 0x24CB3C0;
    DWORD64 dwWeaponC4 = 0x24C9B30;

    bool UpdateOffsets() {
        // Values are hardcoded above.
        // Return true so main.cpp knows initialization succeeded.
        return true;
    }
}
