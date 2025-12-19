#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 绘制场地物品事件
	/// @param 依次为：场地物品，Graphics
	/// @note 时机上先于原版绘制
	class DrawGriditemEvent : public DLLEventTemplate<0x44D14B, 5, REG_ECX, REG_EDX>
	{
	public:
		DrawGriditemEvent(const char* str) : DLLEventTemplate() { Init(str); };
		DrawGriditemEvent(int address) : DLLEventTemplate() { Init(address); };
		DrawGriditemEvent() : DLLEventTemplate() { Init("onDrawGriditem"); };
	};
}