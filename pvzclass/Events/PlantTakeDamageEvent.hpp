#pragma once
#include "DLLEvent.h"

// 植物受到僵尸豌豆伤害事件。
// @param 依次为：植物地址、子弹地址、子弹的 GameObjectType、伤害数值（非引用）
// @return 调整后的伤害数值，负数会取消伤害，
class PlantTakeProjectileDamageEvent : public DLLEvent
{
public:
	PlantTakeProjectileDamageEvent();
	PlantTakeProjectileDamageEvent(const char* name);
};

PlantTakeProjectileDamageEvent::PlantTakeProjectileDamageEvent()
{
	PlantTakeProjectileDamageEvent::PlantTakeProjectileDamageEvent("onPlantTakePeaDamage");
}

PlantTakeProjectileDamageEvent::PlantTakeProjectileDamageEvent(const char* name)
{
	DWORD procAddress = PVZ::Memory::GetProcAddress(name);
	hookAddress = 0x46CFEB;
	rawlen = 6;
	BYTE code[] =
	{
		PUSH_EDX,
		PUSHDWORD(GameObjectType::OBJECT_TYPE_PROJECTILE),
		PUSH_EBP,
		PUSH_EAX,
		INVOKE(procAddress),
		ADD_ESP(16),
		TEST_EUX_EVX(REG_EAX, REG_EAX),
		JNS(8),

		POPAD,
		MOV_ECX(0x46CFFE),
		JMP_REG32(REG_ECX)
	};
	start(STRING(code));
}