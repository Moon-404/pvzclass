#pragma once
#include "../../Events/DLLEvent.h"

namespace PVZEvent
{
	/// @brief 主菜单更新事件
	/// @param 触发事件的主菜单
	class GameSelectorUpdateEvent : public DLLEventTemplate<0x44B2BD, 5, REG_EBP>
	{
	public:
		GameSelectorUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
		GameSelectorUpdateEvent(const char* name) : DLLEventTemplate() { Init(name); };
		GameSelectorUpdateEvent() : GameSelectorUpdateEvent("onGameSelectorUpdate") {};
	};
}
