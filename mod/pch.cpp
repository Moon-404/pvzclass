// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

ExampleMod::ExampleMod()
{
	MOD_TITLE = "示例模组";
	MOD_AUTHOR = "皓月当空dy";
	MOD_VERSION = "0.0";
	MOD_DESCRIPTION = "这是使用pvzclass开发的示例模组";
}

void ExampleMod::onLoad()
{
	std::cout << "ExampleMod is loaded!\n";
}

void ExampleMod::update()
{
	std::cout << "ExampleMod is updated!\n";
}

Mod* getMod()
{
	return new ExampleMod();
}
