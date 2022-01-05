// Copyright [2021] <tiansongyu>

#ifndef IMGUI_DIRECTX_9_KIERO_HOOK_2_GAMESTRUCT_H_
#define IMGUI_DIRECTX_9_KIERO_HOOK_2_GAMESTRUCT_H_

#include <cstdint>

struct vec {
  union {
    struct {
      float x, y, z;
    };
    float v[3];
    int i[3];
  };
  vec() {}
  vec(float _x, float _y, float _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
  }
};

struct vec4 {
  union {
    struct {
      float x, y, z, w;
    };
    float v[4];
    int i[4];
  };
};

struct Matrixf {
  float v[16];

  float operator[](int i) const { return v[i]; }
  float& operator[](int i) { return v[i]; }

  float transformx(const vec& p) const {
    return p.x * v[0] + p.y * v[1] + p.z * v[2] + v[3];
  }

  float transformy(const vec& p) const {
    return p.x * v[4] + p.y * v[5] + p.z * v[6] + v[7];
  }

  float transformz(const vec& p) const {
    return p.x * v[8] + p.y * v[9] + p.z * v[10] + v[11];
  }

  float transformw(const vec& p) const {
    return p.x * v[12] + p.y * v[13] + p.z * v[14] + v[15];
  }

  void transform(const vec& in, vec4* out) const {
    out->x = transformx(in);
    out->y = transformy(in);
    out->z = transformz(in);
    out->w = transformw(in);
  }
};

// BaseAddress + offset
#define GAME_OFFSET(offset) (&(static_cast<char*>(this->baseAddress)[offset])
// Created with ReClass.NET 1.2 by KN4CK3R

// Created with ReClass.NET 1.2 by KN4CK3R

using Vector3 = vec;

// Created with ReClass.NET 1.2 by KN4CK3R

class playerinfo {
 public:
  class player* player_ptr;  // 0x0000
  char pad_0004[12];         // 0x0004
};                           // Size: 0x0010

class entiyList {
 public:
  class playerinfo entList_arry[60];  // 0x0000
  char pad_03C0[220];                 // 0x03C0
};                                    // Size: 0x049C

class player {
 public:
  char pad_0000[148];  // 0x0000
  Vector3 speed;       // 0x0094
  Vector3 pos_1;       // 0x00A0
  Vector3 pos_2;       // 0x00AC
  char pad_00B8[53];   // 0x00B8
  bool isbDormant;     // 0x00ED
  char pad_00EE[6];    // 0x00EE
  bool team;           // 0x00F4
  char pad_00F8[11];   // 0x00F8
  int32_t health;      // 0x0100
  char pad_0104[40];   // 0x0104
  Vector3 angle;       // 0x012C
  Vector3 pos_3;       // 0x0138
  char pad_0144[744];  // 0x0144
};                     // Size: 0x042C

class chara_ptr_info {
 public:
  char pad_0000[8];          // 0x0000
  class player* player_ptr;  // 0x0008
  char pad_000C[4];          // 0x000C
};                           // Size: 0x0010

#endif  // IMGUI_DIRECTX_9_KIERO_HOOK_2_GAMESTRUCT_H_
