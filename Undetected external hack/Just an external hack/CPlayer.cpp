#include "CPlayer.hpp"

CPlayer::CPlayer(int index)
{
	this->ent = NULL;
	this->health = 100;
	this->team = 0;
	this->dormant = true;
	this->index = index;
	this->update();
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	this->ent = mem.readMem<uintptr_t>(client + dwEntityList + this->index * 0x10);

	if (this->ent)
	{
		this->health = mem.readMem<int>(this->ent + m_iHealth);
		this->team = mem.readMem<int>(this->ent + m_iTeamNum);
		this->dormant = mem.readMem<bool>(this->ent + m_bDormant);
	}
}

uintptr_t CPlayer::get()
{
	return this->ent;
}

int CPlayer::getHealth()
{
	return this->health;
}

int CPlayer::getTeam()
{
	return this->team;
}

bool CPlayer::isDormant()
{
	return this->dormant;
}

