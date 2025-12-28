#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 点击拿起工具（如铲子）事件，事件触发于本体函数结束
	class ClickToolEvent : public DLLEventTemplate<0x411F00, 5>
	{
	public:
		ClickToolEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ClickToolEvent(int address) : DLLEventTemplate() { Init(address); };
		ClickToolEvent() : ClickToolEvent("onToolClick") {};
	};
}
