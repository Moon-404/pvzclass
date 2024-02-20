#pragma once

#include "pvzclass.h"
#include "Events/EventHandler.h"
#include <filesystem>

class Mod
{
public:
	std::string MOD_TITLE;
	std::string MOD_AUTHOR;
	std::string MOD_VERSION;
	std::string MOD_DESCRIPTION;
	std::filesystem::path PVZPath, ModPath;
	// 注册需要替换的PAK资源
	void registerAsset(std::filesystem::path source, std::filesystem::path target);
	// 模组被加载时调用一次
	virtual void onLoad(DWORD pid, HANDLE hprocess, HWND mainwindowhandle, int Variable, DWORD mainThreadId, HANDLE hThread, EventHandler& handler) = 0;
	// 这个函数会被无限循环调用
	// 每当把所有模组的 update 都执行一次，就会立即执行下一轮
	// 所以执行间隔与模组的 update 效率之和有关
	virtual void update() = 0;
	// 模组被卸载时调用一次
	virtual void onFree() = 0;
};

