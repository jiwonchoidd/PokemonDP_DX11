#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
class ImGuiManager
{
private:
	bool m_bImguiEnable = true;
public:
	void OnOffImgui();
	bool isImguiEnable();
public:
	void Frame();
	void Render();
public:
	ImGuiManager();
	~ImGuiManager();
};

