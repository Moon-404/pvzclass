#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 手持物品清空事件，事件在本体函数执行前触发
	/// @param Board（本来想用 MousePointer 的，好像也没啥必要）
	/// @note 后续可以加一个是否取消事件的返回值
	class ClearMousePointerEvent : public DLLEventTemplate<0x412330, 6, REG_EDI>
	{
	public:
		ClearMousePointerEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ClearMousePointerEvent(int address) : DLLEventTemplate() { Init(address); };
		ClearMousePointerEvent() : ClearMousePointerEvent("onMousePointerClear") {};
	};
}
