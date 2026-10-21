#include <iostream>
#include <Windows.h>
#include <thread>

#include "Cheats.h"
#include "OS-ImGui/OS-ImGui.h"
#include "Utils/ProcessManager.hpp"
#include "Offsets.h"
#include "Game.h"

int main()
{
    SetConsoleTitleA("VAULTED - Waiting for CS2");
    std::cout << "[*] Waiting for cs2.exe to open..." << std::endl;

    while (ProcessMgr.Attach("cs2.exe") != SUCCEED)
    {
        Sleep(1000);
    }

    std::cout << "[+] Successfully attached to cs2.exe!" << std::endl;
    std::cout << "[*] Initializing offsets..." << std::endl;

    // WAIT FOR CLIENT.DLL TO LOAD
    DWORD64 clientDLL = 0;
    while (clientDLL == 0)
    {
        clientDLL = ProcessMgr.GetProcessModuleHandle("client.dll");
        if (clientDLL == 0)
        {
            std::cout << "[*] Waiting for client.dll to load into memory..." << std::endl;
            Sleep(2000);
        }
    }

    // Hardcoded offsets
    Offset::EntityList = 0x271A908;
    Offset::Matrix = 0x256B020;
    Offset::LocalPlayerController = 0x253CB78;
    Offset::ViewAngle = 0x257BCC8;
    Offset::LocalPlayerPawn = 0x2565718;
    Offset::ForceJump = 0x172C4F0;
    Offset::GlobalVars = 0x2230090;
    Offset::Sensitivity = 0x0; 
    Offset::Sensitivity_Value = 0x0; 
    Offset::PlantedC4 = 0x24CB3C0;
    Offset::WeaponC4 = 0x24C9B30;

    if (!Offset::UpdateOffsets())
    {
        std::cout << "[-] Failed to update offsets." << std::endl;
    }
    
    if (!gGame.InitAddress())
    {
        std::cout << "[-] Failed to initialize game addresses." << std::endl;
        std::cin.get();
        return 1;
    }

    std::cout << "[+] Offsets applied successfully!" << std::endl;
    std::cout << "[*] Initializing Overlay..." << std::endl;

    // Use the OSImGui global instance directly
    // The constructor handles ImGui::CreateContext() internally
    Gui.Window.Size = { 800, 600 };
    Gui.Window.Title = "VAULTED";

    std::cout << "[+] Overlay ready. Press F1 to toggle the menu." << std::endl;

    // Correct Loop for hzqst OS-ImGui
    while (true)
    {
        Gui.NewFrame();
        Cheats::Run();
        Gui.EndFrame();
    }

    return 0;
}
