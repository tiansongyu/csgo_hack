// Copyright [2021] <tiansongyu>

#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "AcGame.h"
#include "base.h"
#include "gamestruct.h"
#include "Util.h"

#define WINDOW_NAME "Dear ImGui DirectX9 Example"
typedef int64_t(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
