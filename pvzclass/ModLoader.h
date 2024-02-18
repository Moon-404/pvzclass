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
	// 加载全部模组
	void loadAll(EventHandler& handler);
	// 调用所有模组的更新
	void update();
	// 卸载全部模组
	void freeAll();
};