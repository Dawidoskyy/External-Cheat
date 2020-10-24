#pragma once
#include "main.hpp"
#include "hack.hpp"

class CPlayer
{
public:

	CPlayer(int index);
	~CPlayer();
	void update();
	uintptr_t get();
	int getHealth();
	int getTeam();
	bool isDormant();

private:

	uintptr_t ent;
	int health;
	int team;
	bool dormant;

	int index;
};