// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

ExampleMod::ExampleMod()
{
	MOD_TITLE = "示例模组1";
	MOD_AUTHOR = "皓月当空dy";
	MOD_VERSION = "0.0";
	MOD_DESCRIPTION = "这是使用pvzclass开发的示例模组";
}

void ExampleMod::onLoad(DWORD pid, HANDLE hprocess, HWND mainwindowhandle, int Variable, DWORD mainThreadId, HANDLE hThread)
{
	PVZ::CopyPVZ(pid, hprocess, mainwindowhandle, Variable, mainThreadId, hThread);
	std::cout << "ExampleMod is loaded!\n";
}

void example1()
{
	if (PVZ::GetPVZApp()->GameState == PVZGameState::Playing)
	{
		auto board = PVZ::GetBoard();
		board->Sun = board->PlayingTime % 10000;
	}
}

void example2()
{
	if (PVZ::GetPVZApp()->GameState == PVZGameState::Playing)
	{
		auto str = std::to_string(PVZ::GetBoard()->PlayingTime);
		Creator::CreateCaption(str.c_str(), str.length(), CaptionStyle::BottomWhite);
	}
}

void ExampleMod::update()
{
	example2();
}

void ExampleMod::onFree()
{
	std::cout << "ExampleMod is freed!\n";
}

Mod* getMod()
{
	return new ExampleMod();
}
