#include <iostream>
#include <Windows.h>
#include <thread>

#include "Cheats.h"
#include "OS-ImGui/OS-ImGui.h"
#include "Utils/ProcessManager.hpp"
#include "Offsets.h"

int main()
{
    SetConsoleTitleA("VAULTED - Waiting for CS2");
    std::cout << "[*] Waiting for cs2.exe to open..." << std::endl;

    // Wait for the game
    while (ProcessMgr.Attach("cs2.exe") != SUCCEED)
    {
        Sleep(1000);
    }

    std::cout << "[+] Successfully attached to cs2.exe!" << std::endl;
    std::cout << "[*] Initializing offsets..." << std::endl;

    DWORD64 clientDLL = ProcessMgr.GetProcessModuleHandle("client.dll");
    if (!clientDLL)
    {
        std::cout << "[-] Failed to get client.dll base." << std::endl;
        std::cin.get();
        return 1;
    }

    // Manually assign the offsets (Note: GlobalVars is plural here)
    Offset::Entity = clientDLL + 0x271A908;
    Offset::Matrix = clientDLL + 0x256B020;
    Offset::LocalPlayerController = clientDLL + 0x253CB78;
    Offset::ViewAngle = clientDLL + 0x257BCC8;
    Offset::LocalPlayerPawn = clientDLL + 0x2565718;
    Offset::ForceJump = clientDLL + 0x172C4F0;
    Offset::GlobalVars = clientDLL + 0x2230090;
    Offset::Sensitivity_Value = clientDLL + 0x0; 
    Offset::PlantedC4 = clientDLL + 0x24CB3C0;
    Offset::WeaponC4 = clientDLL + 0x24C9B30;

    if (!Offset::UpdateOffsets())
    {
        std::cout << "[-] Failed to update offsets." << std::endl;
    }
    else
    {
        std::cout << "[+] Offsets applied successfully!" << std::endl;
    }

    std::cout << "[+] Overlay ready. Press HOME to toggle the menu." << std::endl;

    // Cheats::Run() contains the ImGui render loop
    while (true)
    {
        Cheats::Run();
    }

    return 0;
}
