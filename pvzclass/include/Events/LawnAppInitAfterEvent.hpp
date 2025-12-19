#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 初始化完成事件
	/// @param 触发事件的 PVZApp
	class LawnAppInitAfterEvent : public DLLEventTemplate<0x452292, 6, REG_EBP>
	{
	public:
		LawnAppInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnAppInitAfterEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LawnAppInitAfterEvent() : LawnAppInitAfterEvent("onLawnAppInitAfter") {};
	};
}
