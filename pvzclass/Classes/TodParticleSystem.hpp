#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class BaseClass;
	//Á£×ÓÏµÍ³¡£
	class TodParticleSystem : public BaseClass
	{
	public:
		TodParticleSystem(DWORD indexoraddress);
		T_PROPERTY(BOOLEAN, Dead, __get_Dead, __set_Dead, 0x1C);
		void OverrideColor(const char* emitter_name, const Color color);
		void OverrideExtraAdditiveDraw(boolean isEnable);
	};
	std::vector<TodParticleSystem> GetAllParticleSystem();
	PVZ::TodParticleSystem CreateParticleSystem(float X, float Y, int render_order, EffectType::EffectType type);
}
