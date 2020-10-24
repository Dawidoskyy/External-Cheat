#include "menu.hpp"

static bool init = false;

void ColorPicker(const char* name, float* color, bool alpha)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiStyle* style = &ImGui::GetStyle();

	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;

	ImGui::SameLine(219.f);
	ImGui::ColorEdit4(std::string{ "##" }.append(name).append("Picker").c_str(), color, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);

}

void initalize()
{
	ImGui::SetNextWindowSize(ImVec2(385, 262));
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.f;

	init = true;
}

void render()
{
	if (!init) initalize();

	ImGui::Begin("Free hack", nullptr, windowFlags);

	if (!foundCS)
	{
		ImGui::Text("Please open CS:GO");
		ImGui::End();
		return;
	}

	ImGui::Checkbox("Enemy glow", &enemyGlow);
	ColorPicker("Enemy color", enemyColor, false);
	ImGui::SliderFloat("Glow alpha", &enemyColor[3], 0.f, 1.f);
	ImGui::Combo("Glow type", &enemyType, "Default\0Pulse\0Arms race");

	ImGui::Checkbox("Team glow", &teamGlow);
	ColorPicker("Team color", teamColor, false);
	ImGui::SliderFloat("Glow alpha ", &teamColor[3], 0.f, 1.f);
	ImGui::Combo("Glow type ", &teamType, "Default\0Pulse\0Arms race");

	ImGui::Separator();

	ImGui::Checkbox("Bunny hop", &doBhop);
	ImGui::Checkbox("No flash", &noFlash);
	ImGui::Checkbox("+15 Fov", &doFov);
	ImGui::Checkbox("Reveal enemies on radar", &revealRadar);
	
	ImGui::Separator();
	
	ImGui::Separator();
	
    ImGui::Text("https://github.com/Dawidoskyy");
	ImGui::Text("Public undetected external cheat");
	ImGui::Text("Status: Undetected");
	ImGui::End();
}