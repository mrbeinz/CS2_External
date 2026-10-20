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

    // Wait until CS2 is open and we successfully attach
    while (ProcessMgr.Attach("cs2.exe") != SUCCEED)
    {
        Sleep(1000);
    }

    std::cout << "[+] Successfully attached to cs2.exe!" << std::endl;
    std::cout << "[*] Initializing offsets..." << std::endl;

    // Get the base address of client.dll
    DWORD64 clientDLL = ProcessMgr.GetProcessModuleHandle("client.dll");
    if (!clientDLL)
    {
        std::cout << "[-] Failed to get client.dll base." << std::endl;
        std::cin.get();
        return 1;
    }

    // Manually assign the offsets so we don't need the pattern scanner
    Offset::EntityList = clientDLL + 0x271A908;
    Offset::Matrix = clientDLL + 0x256B020;
    Offset::LocalPlayerController = clientDLL + 0x253CB78;
    Offset::ViewAngle = clientDLL + 0x257BCC8;
    Offset::LocalPlayerPawn = clientDLL + 0x2565718;
    Offset::ForceJump = clientDLL + 0x172C4F0;
    Offset::GlobalVar = clientDLL + 0x2230090;
    Offset::PlantedC4 = clientDLL + 0x24CB3C0;
    Offset::WeaponC4 = clientDLL + 0x24C9B30;

    // Call UpdateOffsets just in case any other code expects it
    if (!Offset::UpdateOffsets())
    {
        std::cout << "[-] Failed to update offsets." << std::endl;
    }
    else
    {
        std::cout << "[+] Offsets applied successfully!" << std::endl;
    }

    std::cout << "[*] Initializing Overlay..." << std::endl;

    OS_ImGui ImGui;
    if (!ImGui.Init())
    {
        std::cout << "[-] Failed to initialize ImGui overlay." << std::endl;
        std::cin.get();
        return 1;
    }

    // Set the window title (you can change this if you want)
    ImGui.SetWindowTitle("VAULTED");
    
    // Set a default window size
    ImGui.SetWindowSize({ 800, 600 });

    std::cout << "[+] Overlay initialized. Press HOME to toggle the menu." << std::endl;

    // Main cheat loop
    while (true)
    {
        Cheats::Run();
    }

    return 0;
}
