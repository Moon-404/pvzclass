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
	// 递归加载路径
	// stage 1资源包 2dll模组
	void loadPath(std::filesystem::path p, EventHandler& handler, int stage);
public:
	std::filesystem::path PVZPath;
	// 加载全部资源
	void loadAsset(EventHandler& handler);
	// 加载全部模组
	void loadDll(EventHandler& handler);
	// 调用所有模组的更新
	void update();
	// 卸载全部模组
	void freeAll();
};