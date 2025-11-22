#pragma once
#include "../PVZ.h"

namespace PVZ
{
	/// @brief 动画缓存类。存储植物、僵尸、小推车的绘图的图片。
	class ReanimatorCache
	{
	public:
		static void SetMemSize(byte zombie_num = 35, DWORD lawnmower_num = 4);
	};
}