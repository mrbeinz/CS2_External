#include "Offsets.h"
#include "Game.h"
#include "Utils/ProcessManager.hpp"

namespace Offset {
    // Hardcoded from your dumper
    DWORD64 EntityList = 0x271A908;
    DWORD64 Matrix = 0x256B020;
    DWORD64 LocalPlayerController = 0x253CB78;
    DWORD64 ViewAngle = 0x257BCC8;
    DWORD64 LocalPlayerPawn = 0x2565718;
    DWORD64 ForceJump = 0x172C4F0; // Standard CS2 bhop offset
    DWORD64 GlobalVar = 0x2230090;
    DWORD64 Sensitivity_Value = 0x0; 
    DWORD64 PlantedC4 = 0x24CB3C0;
    DWORD64 WeaponC4 = 0x24C9B30;

    namespace Pawn {
        DWORD64 m_iHealth = 0x34C;
        DWORD64 m_iTeamNum = 0x3E7;
        DWORD64 m_flFlashDuration = 0x1510;
    }

    bool UpdateOffsets() {
        return true;
    }
}
