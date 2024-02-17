#pragma once

#include "pvzclass.h"

class Mod
{
public:
	std::string MOD_TITLE;
	std::string MOD_AUTHOR;
	std::string MOD_VERSION;
	std::string MOD_DESCRIPTION;
	// 模组被加载时调用一次
	virtual void onLoad() = 0;
	// 这个函数会被无限循环调用
	// 每当把所有模组的 update 都执行一次，就会立即执行下一轮
	// 所以执行间隔与模组的 update 效率之和有关
	virtual void update() = 0;
};

