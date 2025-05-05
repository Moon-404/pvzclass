#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class BaseClass;

	/// @brief 植物定义类，存储植物相关的若干常量。
	class PlantDefinition : public BaseClass
	{
	public:
		PlantDefinition(SeedType::SeedType type);
		/// @brief 植物类型
		T_READONLY_PROPERTY(SeedType::SeedType, Type, __get_Type, 0);
		/// @brief 植物的默认动画类型
		T_READONLY_PROPERTY(AnimationType::AnimationType, AnimType, __get_AnimType, 8);
		INT_READONLY_PROPERTY(PacketID, __get_PacketID, 0xC);
		/// @brief 基础阳光消耗
		INT_PROPERTY(Cost, __get_Cost, __set_Cost, 0x10);
		/// @brief 基础种植冷却时间
		INT_PROPERTY(Cooldown, __get_Cooldown, __set_Cooldown, 0x14);
		/// @brief 植物默认子类型。原版只有非射手（0）与射手（1）之分。
		INT_PROPERTY(SubClass, __get_SubClass, __set_SubClass, 0x18);
		/// @deprecated
		INT_PROPERTY(IsShooter, __get_IsShooter, __set_IsShooter, 0x18);
		/// @brief 基础攻击间隔
		INT_PROPERTY(AttackCooldown, __get_AttackCooldown, __set_AttackCooldown, 0x1C);
	};
	/// @brief 获取指定植物类型的定义
	/// @param type 植物类型
	/// @return 该类型植物对应的 PlantDefinition
	PlantDefinition GetPlantDefinition(SeedType::SeedType type);
}