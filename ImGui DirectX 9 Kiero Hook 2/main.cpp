// Copyright [2021] <tiansongyu>

#include "includes.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

bool isDisplay = true;
bool isFirst = true;
bool isBox = true;

AcGame* acgame;
void InitImGui(LPDIRECT3DDEVICE9 pDevice) {
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
  ImGui_ImplWin32_Init(window);

  RECT WindowsRect;
  GetClientRect(window, &WindowsRect);
  AC::Base::WindowWidth = WindowsRect.right - WindowsRect.left;
  AC::Base::WindowHeigth = WindowsRect.bottom - WindowsRect.top;

  ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
int64_t __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
  if (!init) {
    InitImGui(pDevice);
    init = true;
  }

  ImGui_ImplDX9_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("ImGui Window");

  if (isFirst) {
    acgame = new AcGame();
    acgame->Init();
    isFirst = false;

    /*AllocConsole();
    FILE* f = new FILE();
    freopen_s(&f, "CONOUT$", "w", stdout);*/
  }

  if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z)))
    isDisplay = !isDisplay;

  if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z))) isBox = !isBox;

  if (isDisplay) {
    acgame->Update();
    if (acgame->numPlayers > 0 && acgame->numPlayers < 50 && isBox)
      acgame->DrawBox();
  }

  ImGui::End();

  ImGui::EndFrame();
  ImGui::Render();
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

  return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam,
                          LPARAM lParam) {
  if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    return true;

  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
  DWORD wndProcId;
  GetWindowThreadProcessId(handle, &wndProcId);

  if (GetCurrentProcessId() != wndProcId) return TRUE;  // skip to next window

  window = handle;
  return FALSE;  // window found abort search
}

HWND GetProcessWindow() {
  window = NULL;
  EnumWindows(EnumWindowsCallback, NULL);
  return window;
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
  bool attached = false;
  do {
    if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
      kiero::bind(42, reinterpret_cast<void**> & oEndScene, hkEndScene);
      do
        window = GetProcessWindow();
      while
        (window == NULL);
      oWndProc =
          (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
      attached = true;
    }
  } while (!attached);
  return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
  switch (dwReason) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hMod);
      CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
      break;
    case DLL_PROCESS_DETACH:
      kiero::shutdown();
      break;
  }
  return TRUE;
}
