#include "Offsets.h"
#include "Game.h"
#include "Utils/ProcessManager.hpp"

namespace Offset {
    DWORD64 Entity = 0x271A908;
    DWORD64 Matrix = 0x256B020;
    DWORD64 LocalPlayerController = 0x253CB78;
    DWORD64 ViewAngle = 0x257BCC8;
    DWORD64 LocalPlayerPawn = 0x2565718;
    DWORD64 ForceJump = 0x172C4F0;
    DWORD64 GlobalVars = 0x2230090;
    DWORD64 Sensitivity = 0x0;
    DWORD64 PlantedC4 = 0x24CB3C0;
    DWORD64 WeaponC4 = 0x24C9B30;

    PawnOffsets Pawn;

    bool UpdateOffsets() {
        return true;
    }
}
