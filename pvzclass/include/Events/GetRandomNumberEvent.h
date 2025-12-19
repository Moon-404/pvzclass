#pragma once
#include "DLLEvent.h"

/// @brief 获取新的随机数事件
/// @param 原随机数
/// @return 新的随机数
/// @note 原随机数函数会返回一个 0-0x7FFFFFFF 的随机数\n
/// 无论是 Rand(int) 还是 Rand(float) 最后都还是从这个随机数出发的\n
/// 所以只要专注于控制这个 0-0x7FFFFFFF 的随机整数就可以控制游戏的随机数了
class GetRandomNumberEvent : public DLLEvent
{
public:
	GetRandomNumberEvent() : GetRandomNumberEvent("onRandomNumberGet") {};
	GetRandomNumberEvent(const char* str) : GetRandomNumberEvent(PVZ::Memory::GetProcAddress(str)) {};
	GetRandomNumberEvent(int address)
	{
		hookAddress = 0x5A9A37;
		rawlen = 5;
		BYTE code[] = { PUSH_EAX, INVOKE(address), ADD_ESP(4), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
		start(STRING(code));
	}
};
