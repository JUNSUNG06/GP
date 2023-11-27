
#include "pch.h"
#include "BaseWindow.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(325);
    BaseWindow game({ GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) });
    game.Run(hInstance, lpCmdLine, nCmdShow);
}