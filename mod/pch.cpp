// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include <thread>

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

ExampleMod::ExampleMod()
{
	MOD_TITLE = "示例模组1";
	MOD_AUTHOR = "皓月当空dy";
	MOD_VERSION = "";
	MOD_DESCRIPTION = "将游戏时间以字幕形式显示";
}

void ExampleMod::onLoad(DWORD pid, HANDLE hprocess, HWND mainwindowhandle, int Variable, DWORD mainThreadId, HANDLE hThread, EventHandler& handler)
{
	PVZ::CopyPVZ(pid, hprocess, mainwindowhandle, Variable, mainThreadId, hThread);
	std::cout << "ExampleMod is loaded!\n";
}

void caption()
{
	auto str = std::to_string(PVZ::GetBoard()->PlayingTime);
	Creator::CreateCaption(str.c_str(), str.length(), CaptionStyle::BottomWhite);
}

void ExampleMod::update()
{
	if (PVZ::GetPVZApp()->GameState == PVZGameState::Playing)
	{
		std::thread t(caption);
		t.detach();
	}
}

void ExampleMod::onFree()
{
	std::cout << "ExampleMod is freed!\n";
}

Mod* getMod()
{
	return new ExampleMod();
}
