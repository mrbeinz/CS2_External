#include "Offsets.h"

namespace Offset {
    DWORD64 Entity = 0x0;
    DWORD64 Matrix = 0x0;
    DWORD64 LocalPlayerController = 0x0;
    DWORD64 ViewAngle = 0x0;
    DWORD64 LocalPlayerPawn = 0x0;
    DWORD64 ForceJump = 0x0;
    DWORD64 GlobalVars = 0x0; // Plural
    DWORD64 Sensitivity_Value = 0x0;
    DWORD64 PlantedC4 = 0x0;
    DWORD64 WeaponC4 = 0x0;

    // Instantiate the structs
    GlobalVarOffsets GlobalVar;
    PawnOffsets Pawn;

    bool UpdateOffsets() {
        return true;
    }
}
