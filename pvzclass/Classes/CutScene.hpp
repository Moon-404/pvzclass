#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class CutScene : public BaseClass
	{
	public:
		CutScene(int address);
		/// @brief 是否已经放置街上的僵尸
		T_PROPERTY(BOOLEAN, PlacedZombies, __get_PlacedZombies, __set_PlacedZombies, 0x35);
		/// @brief 放置街上的僵尸
		/// @note x 和 y 是街上的坐标，不是场地中的格子坐标
		/// @note x 和 y 的取值应该是 0,1,2,3,4
		/// @note 在植物僵尸 2 关卡中，创建鸭子救生圈僵尸会转化为创建豌豆射手僵尸。
		void PlaceStreetZombie(ZombieType::ZombieType type, int x, int y);
	};
}
