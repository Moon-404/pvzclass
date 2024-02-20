#pragma once

#include "pvzclass.h"
#include "Mod.h"
#include "Events/EventHandler.h"
#include <iostream>
#include <filesystem>
#include <Psapi.h>

class ModLoader
{
private:
	std::vector<Mod*> mods;
	std::vector<HMODULE> dlls;
	void loadPath(std::filesystem::path p, EventHandler& handler);
public:
	std::filesystem::path PVZPath;
	// ����ȫ��ģ��
	void loadAll(EventHandler& handler);
	// ��������ģ��ĸ���
	void update();
	// ж��ȫ��ģ��
	void freeAll();
};