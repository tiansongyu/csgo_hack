// Copyright [2021] <tiansongyu>

#ifndef IMGUI_DIRECTX_9_KIERO_HOOK_2_ACGAME_H_
#define IMGUI_DIRECTX_9_KIERO_HOOK_2_ACGAME_H_

#include <Windows.h>

#include <cstdint>
#include <vector>

#include "AcGame.h"
#include "Util.h"
#include "base.h"
#include "gamestruct.h"
#include "imgui/imgui.h"


class playerinfo_t {
 public:
  bool isValid = false;
  player* ent = nullptr;
  vec pos2D{};
  vec pos3D{};
  vec headpos3D{};
  vec headpos2D{};

  playerinfo_t(player* ent, float width, float height);
};

class AcGame {
 public:
  void Init();

  void Update() {
    this->numPlayers = *reinterpret_cast<int*>GAME_OFFSET(0x522117C);
    this->entiylist = reinterpret_cast<entiyList*>GAME_OFFSET(0x4dd0aB4);
    this->local_player = reinterpret_cast<player*>GAME_OFFSET(0xdb558c);
  }
  void DrawBox();

  void DrawOnePlayer(playerinfo_t* playerinfo);

 public:
  // init once
  int baseAddress = 0;
  player* local_player = nullptr;
  entiyList* entiylist = nullptr;
  // need to update
  int numPlayers = 0;

 private:
  void SetModuleBaseAddress(WCHAR* str);
  void Init_base_address();
};

#endif  // IMGUI_DIRECTX_9_KIERO_HOOK_2_ACGAME_H_
