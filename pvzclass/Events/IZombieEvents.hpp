#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief IZE 关主题植物初始化事件
	/// @param 触发事件的 Challenge
	/// @return 是否初始化植物
	class IZESetupThemeEvent : public BoolDLLEventTemplate<0x42B041, 5, 0x42B277, REG_EDI>
	{
	public:
		IZESetupThemeEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		IZESetupThemeEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		IZESetupThemeEvent() : IZESetupThemeEvent("onIZESetupTheme") {};
	};
}
