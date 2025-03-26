#pragma once
#include "DLLEvent.h"

// 植物受到啃食伤害事件。
// 此事件不考虑 IZ 模式下的双倍伤害。若要手动避免，请另行结算后取消伤害，
// @param 依次为：植物地址、僵尸地址、GameObjectType::OBJECT_TYPE_NONE、伤害数值（非引用）
// @return 调整后的伤害数值，负数会取消伤害，
class PlantTakeEatDamageEvent : public DLLEvent
{
public:
	PlantTakeEatDamageEvent();
	PlantTakeEatDamageEvent(const char* name);
};

PlantTakeEatDamageEvent::PlantTakeEatDamageEvent()
{
	PlantTakeEatDamageEvent::PlantTakeEatDamageEvent("onPlantTakeEatDamage");
}

PlantTakeEatDamageEvent::PlantTakeEatDamageEvent(const char* name)
{
	DWORD procAddress = PVZ::Memory::GetProcAddress(name);
	hookAddress = 0x52FCF0;
	rawlen = 7;
	BYTE code[] =
	{
		PUSH(4),
		PUSHDWORD(GameObjectType::OBJECT_TYPE_NONE),
		PUSH_EBP,
		PUSH_ESI,
		INVOKE(procAddress),
		ADD_ESP(16),
		TEST_EUX_EVX(REG_EAX, REG_EAX),
		JNS(8),

		POPAD,
		MOV_ECX(0x52FD2E),
		JMP_REG32(REG_ECX)
	};
	start(STRING(code));
}

// 植物受到子弹伤害事件。
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
	PlantTakeProjectileDamageEvent::PlantTakeProjectileDamageEvent("onPlantTakeProjectileDamage");
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