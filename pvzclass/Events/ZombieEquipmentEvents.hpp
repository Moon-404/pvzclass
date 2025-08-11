#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸失去盾牌事件
	/// @param 触发事件时的僵尸
	class ZombieDetachShieldEvent : public DLLEventTemplate<0x5330E0, 5, REG_EAX>
	{
	public:
		ZombieDetachShieldEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDetachShieldEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieDetachShieldEvent() : ZombieDetachShieldEvent("onZombieDetachShield") {};
	};
}