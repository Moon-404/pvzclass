#pragma once
#include "DLLEvent.h"

/// @brief 僵尸灰烬事件
/// @param 触发事件的僵尸
/// @note 僵尸受到灰烬伤害就会触发
/// @note 该事件不可被取消。若希望取消该事件以实现免疫灰烬，请考虑 ZombieBurntEvent。
/// @note 该事件不与 ZombieBurntEvent 兼容，请不要同时使用。
/// @see ZombieBurntEvent
class ZombieBlastEvent : public DLLEventTemplate<0x532B70, 6, REG_ECX>
{
public:
	ZombieBlastEvent();
};

ZombieBlastEvent::ZombieBlastEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieBlast");
	hookAddress = 0x532B70;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}

/// @brief 僵尸受到灰烬伤害事件。
/// @param 触发事件的僵尸
/// @return 是否取消该事件。
/// @note 该事件不与 ZombieBlastEvent 兼容，请不要同时使用。
/// @see ZombieBlastEvent
class ZombieBurntEvent : public DLLEvent
{
public:
	ZombieBurntEvent(int address);
};

ZombieBurntEvent::ZombieBurntEvent(int address)
{
	hookAddress = 0x532B70;
	rawlen = 6;
	BYTE code[] =
	{
		PUSH_ECX,
		INVOKE(address),
		MOV_EUX_EVX(REG_ECX, REG_EAX),
		ADD_ESP(4),

		TEST_EUX_EVX(REG_ECX, REG_ECX),
		JNZ(2),
		POPAD,
		RET
	};
	start(STRING(code));
}