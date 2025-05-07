#pragma once
#include "DLLEvent.h"

// 植物被啃死事件。
/// @param 依次为：触发事件的植物、啃食该植物的僵尸。
/// @return 是否继续结算原版的结算过程。
class PlantEatenEvent : public BoolDLLEventTemplate<0x52FD3D, 5, 0x52FDEE, REG_EBP, REG_ESI>
{
public:
	PlantEatenEvent() : BoolDLLEventTemplate() { Init("onPlantEaten"); };
};