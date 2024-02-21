#pragma once

#include "pvzclass.h"
#include "Mod.h"
#include "Events/EventHandler.h"
#include <iostream>
#include <filesystem>
#include <Psapi.h>
#include "json.hpp"
#include <fstream>

class ModLoader
{
private:
	std::vector<Mod*> mods;
	std::vector<HMODULE> dlls;
	nlohmann::json assets;
	// �ݹ����·��
	// stage 1��Դ�� 2dllģ��
	void loadPath(std::filesystem::path p, EventHandler& handler, int stage);
public:
	std::filesystem::path PVZPath;
	// ����ȫ����Դ
	void loadAsset(EventHandler& handler);
	// ����ȫ��ģ��
	void loadDll(EventHandler& handler);
	// ��������ģ��ĸ���
	void update();
	// ж��ȫ��ģ��
	void freeAll();
};