#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 植物索敌僵尸事件
	/// @note 该事件只重载行差判定和类型判定
	/// @param 触发事件的植物，植物判定的僵尸，索敌行
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class PlantFindTargetRTEvent : public ThreeStateEventTemplate<0x467614, 6, 0x4676C8, 0x467884, MEM_ESP_ADD(0x74), REG_ESI, REG_EDI>
	{
	public:
		PlantFindTargetRTEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		PlantFindTargetRTEvent(int address) : ThreeStateEventTemplate() { Init(address); };
		PlantFindTargetRTEvent() : PlantFindTargetRTEvent("onPlantFindTargetRT") {};
	};

	/// @brief 窝瓜索敌僵尸事件
	/// @note 该事件只重载行差判定和类型判定
	/// @param 触发事件的植物，植物判定的僵尸
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class SquashFindTargetRTEvent : public ThreeStateEventTemplate<0x460829, 6, 0x460859, 0x46099F, REG_EBX, REG_EBP>
	{
	public:
		SquashFindTargetRTEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		SquashFindTargetRTEvent(int address) : ThreeStateEventTemplate() { Init(address); };
		SquashFindTargetRTEvent() : SquashFindTargetRTEvent("onSquashFindTargetRT") {};
	};

	/// @brief 杨桃索敌僵尸事件
	/// @note 优先级低于 PVZ::DamageRangeFlags 的判别，高于其他判定
	/// @param 触发事件的植物，植物判定的僵尸
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class StarfruitFindTargetEvent : public ThreeStateEventTemplate<0x45F4F1, 6, 0x45F6D1, 0x45F6AD, REG_EBX, REG_ECX>
	{
	public:
		StarfruitFindTargetEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		StarfruitFindTargetEvent(int address) : ThreeStateEventTemplate() { Init(address); };
		StarfruitFindTargetEvent() : StarfruitFindTargetEvent("onStarFruitFindTarget") {};
	};
}
