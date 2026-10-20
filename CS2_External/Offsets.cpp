#include "Offsets.h"

namespace Offset {
    DWORD64 EntityList = 0x0;
    DWORD64 Matrix = 0x0;
    DWORD64 LocalPlayerController = 0x0;
    DWORD64 ViewAngle = 0x0;
    DWORD64 LocalPlayerPawn = 0x0;
    DWORD64 ForceJump = 0x0;
    DWORD64 GlobalVars = 0x0;
    DWORD64 Sensitivity = 0x0;
    DWORD64 Sensitivity_Value = 0x0;
    DWORD64 PlantedC4 = 0x0;
    DWORD64 WeaponC4 = 0x0;

    // Instantiate all structs
    GlobalVarOffsets GlobalVar;
    EntityOffsets Entity;
    PawnOffsets Pawn;
    WeaponOffsets Weapon;

    bool UpdateOffsets() {
        return true;
    }
}
