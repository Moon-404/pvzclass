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
	// 加载全部模组
	void loadAll(EventHandler& handler);
	// 调用所有模组的更新
	void update();
	// 卸载全部模组
	void freeAll();
};