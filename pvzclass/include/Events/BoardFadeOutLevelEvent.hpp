#pragma once
#include "../../Events/DLLEvent.h"

namespace PVZEvent
{
	/// @brief 淡出当前关卡（或当前阶段）事件
	/// @param 触发事件的 PVZ::Board
	/// @return 是否执行原版的淡出过程
	class BoardFadeOutLevelEvent : public BoolDLLEventTemplate<0x40C3E0, 8, 0x40CA03, REG_ECX>
	{
	public:
		BoardFadeOutLevelEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		BoardFadeOutLevelEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		BoardFadeOutLevelEvent() : BoardFadeOutLevelEvent("onBoardFadeOutLevel") {};
	};
}
