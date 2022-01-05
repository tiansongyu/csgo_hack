// Copyright [2021] <tiansongyu>

#ifndef IMGUI_DIRECTX_9_KIERO_HOOK_2_BASE_H_
#define IMGUI_DIRECTX_9_KIERO_HOOK_2_BASE_H_
#include "gamestruct.h"
// this->entiylist = *(entiyList**)(BaseAddress + 0x187c10);
// this->numPlayers = *(int*)(BaseAddress + 0x18EFE4);
// this->local_player = *(player**)(BaseAddress + 0x17B0B8);
bool WorldToScreen(vec pos3D, vec* pos2D);

enum { ALIVE, DIED };

namespace AC {
namespace Base {
extern int WindowWidth;
extern int WindowHeigth;
extern Matrixf* MatrixAddress;
}  // namespace Base
};  // namespace AC

#endif  // IMGUI_DIRECTX_9_KIERO_HOOK_2_BASE_H_
