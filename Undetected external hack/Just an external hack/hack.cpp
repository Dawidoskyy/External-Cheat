#include "hack.hpp""

Memory mem = Memory::Memory();
uintptr_t procId = NULL;
uintptr_t client = NULL;
uintptr_t engine = NULL;

struct GlowStruct
{
	BYTE base[4];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

void run()
{
	while (!foundCS)
	{
		procId = mem.getProcess(L"csgo.exe");

		if (procId)
			foundCS = true;

		Sleep(100);
	}

	client = mem.getModule(procId, L"client.dll");
	engine = mem.getModule(procId, L"engine.dll");

	uintptr_t glowObj = mem.readMem<uintptr_t>(client + dwGlowObjectManager);
	while (!glowObj)
	{
		glowObj = mem.readMem<uintptr_t>(client + dwGlowObjectManager);
		Sleep(100);
	}

	while (true)
	{
		uintptr_t pLocal = mem.readMem<uintptr_t>(client + dwLocalPlayer);
		if (!pLocal)
		{
			Sleep(100);
			continue;
		}
		int localTeam = mem.readMem<int>(pLocal + m_iTeamNum);

		if (mem.readMem<float>(pLocal + m_flFlashDuration) > 0.f && noFlash)
		{
			mem.writeMem<float>(pLocal + m_flFlashDuration, 0.f);
		}
		
		if (mem.readMem<float>(pLocal + m_iFOV) > 60.f && doFov)
		{
			mem.writeMem<float>(pLocal + m_iFOV, 75);
		}

		if (doBhop && GetAsyncKeyState(VK_SPACE) && (mem.readMem<BYTE>(pLocal + m_fFlags) & (1 << 0)))
		{
			mem.writeMem<int>(client + dwForceJump, 6);
		}
		

		for (int i = 0; i < 64; i++)
		{
			CPlayer player = CPlayer::CPlayer(i);

			if (!player.get() || player.isDormant() || player.getHealth() < 1) continue;

			mem.writeMem<bool>(player.get() + m_bSpotted, revealRadar);

			int glowIndex = mem.readMem<int>(player.get() + m_iGlowIndex);

			GlowStruct glow;
			glow = mem.readMem<GlowStruct>(glowObj + glowIndex * 0x38);

			if (teamGlow && localTeam == player.getTeam())
			{
				glow.red = teamColor[0];
				glow.green = teamColor[1];
				glow.blue = teamColor[2];
				glow.alpha = teamColor[3];
				glow.glowStyle = teamType;
			}
			else if (enemyGlow)
			{
				glow.red = enemyColor[0];
				glow.green = enemyColor[1];
				glow.blue = enemyColor[2];
				glow.alpha = enemyColor[3];
				glow.glowStyle = enemyType;
			}
			glow.renderWhenOccluded = true;
			glow.renderWhenUnOccluded = false;

			mem.writeMem<GlowStruct>(glowObj + glowIndex * 0x38, glow);
		}

		Sleep(1);
	}
}