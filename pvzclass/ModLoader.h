#pragma once

#include "pvzclass.h"
#include "Mod.h"
#include "Events/EventHandler.h"
#include <iostream>
#include <filesystem>

class ModLoader
{
private:
	std::vector<Mod*> mods;
	std::vector<HMODULE> dlls;
public:
	// ����ȫ��ģ��
	void loadAll(EventHandler& handler);
	// ��������ģ��ĸ���
	void update();
	// ж��ȫ��ģ��
	void freeAll();
};