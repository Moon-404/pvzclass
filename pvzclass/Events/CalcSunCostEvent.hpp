#pragma once
#include "DLLEvent.h"

class CalcSunCostEvent : public IntDLLEventTemplate<0x467B06, 6, 0, 0, 0, REG_EAX, true, REG_EAX>
{
public:
	CalcSunCostEvent() : IntDLLEventTemplate() { Init("getCardCost"); };
};
