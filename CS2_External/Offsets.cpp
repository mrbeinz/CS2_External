#include "Offsets.h"
#include "Game.h"
#include "Utils/ProcessManager.hpp"

namespace Offsets {
    uint64_t dwEntityList = 0x271A908;
    uint64_t dwLocalPlayerController = 0x253CB78;
    uint64_t dwViewMatrix = 0x256B020;
    uint64_t dwViewAngles = 0x257BCC8;
    uint64_t dwGlobalVars = 0x2230090;
    uint64_t dwPlantedC4 = 0x24CB3C0;
    uint64_t dwWeaponC4 = 0x24C9B30;

    void Initialize() {
        // Values are hardcoded above based on the latest dump.
        // If the game updates, update the hex values above.
    }
}
