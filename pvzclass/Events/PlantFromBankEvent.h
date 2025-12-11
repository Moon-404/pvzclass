#pragma once
#include "DLLEvent.h"

/// @brief 植物从卡槽中被种植事件。
/// @note 触发事件时，植物已创建完成，卡片还没进入冷却。
/// @param 依次为：被种植的植物、卡片在卡槽中的位置下标（注意不是卡槽的地址）。
class PlantFromBankEvent : public DLLEventTemplate<0x410AC4, 6, REG_EAX, REG_ESI>
{
public:
	PlantFromBankEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantFromBankEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantFromBankEvent() : PlantFromBankEvent("onPlantFromBank") {};
};
