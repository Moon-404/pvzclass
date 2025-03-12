#pragma once
#include "DLLEvent.h"

// 植物初始化之后的事件。
// 无返回值
// @param 依次为：触发事件的植物。
class PlantInitAfterEvent : public DLLEvent
{
public:
	PlantInitAfterEvent();
};

PlantInitAfterEvent::PlantInitAfterEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPlantInitAfter");
	hookAddress = 0x45E7A3;
	rawlen = 7;
	BYTE code[] =
	{
		PUSH_ESI,
		INVOKE(procAddress),
		ADD_ESP(4),
	};
	start(STRING(code));
}