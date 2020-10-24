#pragma once
#include "main.hpp"
#include "memory.hpp"
#include "CPlayer.hpp"

extern Memory mem;
extern uintptr_t procId, client, engine;

void run();