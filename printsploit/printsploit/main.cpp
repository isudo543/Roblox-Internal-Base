#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include "rbx/update/update.h"

extern "C" __declspec(dllexport) LRESULT CALLBACK UwpHook(int code, WPARAM wParam, LPARAM lParam) {
    return CallNextHookEx(NULL, code, wParam, lParam);
}

void bypass() { /* just say to be here lmao */
    RBX::Print(1, "Bypass module injected");
    RBX::Print(2, "Abyss is undetected btw ;3");
}

BOOL APIENTRY DllMain(HMODULE hMod, ULONG ulReason, LPVOID) {
    switch (ulReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        std::thread(bypass).detach();
       break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;

}
