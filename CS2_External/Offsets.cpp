#include "Offsets.h"
#include "Utils/ProcessManager.hpp"
#include "Game.h"

// This function is typically called in main() to initialize the offsets
bool Offsets::Initialize()
{
    // FIX 1: Removed the illegal reinterpret_cast. GetProcessModuleHandle already returns DWORD64.
    DWORD64 ClientDLL = ProcessMgr.GetProcessModuleHandle("client.dll");
    if (!ClientDLL) return false;

    DWORD64 EngineDLL = ProcessMgr.GetProcessModuleHandle("engine2.dll");

    // FIX 2: SearchMemory returns a std::vector<DWORD64>. 
    // You must add [0] to grab the first result, or it will fail to compile.

    // Example for GlobalVars (Replace the "" with your actual signature pattern)
    // DWORD64 globalVars = ProcessMgr.SearchMemory("48 89 15 ?? ?? ?? ?? 48 89 42", ClientDLL, 0xFFFFFF)[0];
    
    // Example for EntityList
    // DWORD64 entityList = ProcessMgr.SearchMemory("48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB", ClientDLL, 0xFFFFFF)[0];

    // Example for LocalPlayerController
    // DWORD64 localPlayerController = ProcessMgr.SearchMemory("48 8B 05 ?? ?? ?? ?? 41 89 BE", ClientDLL, 0xFFFFFF)[0];

    // Example for ViewMatrix
    // DWORD64 viewMatrix = ProcessMgr.SearchMemory("48 8D 0D ?? ?? ?? ?? 48 C1 E0 06", ClientDLL, 0xFFFFFF)[0];

    // Assign them to your global variables here
    // gGame.SetGlobalVars(globalVars - ClientDLL);
    // gGame.SetEntityList(entityList - ClientDLL);
    // etc...

    return true;
}
