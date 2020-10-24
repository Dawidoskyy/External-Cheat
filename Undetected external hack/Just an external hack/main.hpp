#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <Windows.h>
#include <dinput.h>
#include <tchar.h>
#include <d3d9.h>
#include <thread>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_internal.h"
#include "menu.hpp"
#include "hack.hpp"
#include "csgo.hpp"
#define DIRECTINPUT_VERSION 0x0800

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

extern bool foundCS;
extern bool hackInit;
extern bool doBhop;
extern bool revealRadar;
extern bool noFlash;
extern bool Clantag;
extern bool doFov;
extern bool enemyGlow;
extern bool teamGlow;
extern float enemyColor[];
extern float teamColor[];
extern int enemyType;
extern int teamType;
	