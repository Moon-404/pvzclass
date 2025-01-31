#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class BaseClass;
	//粒子系统。
	class TodParticleSystem : public BaseClass
	{
	public:
		TodParticleSystem(DWORD indexoraddress);
		T_PROPERTY(BOOLEAN, Dead, __get_Dead, __set_Dead, 0x1C);
		// @brief 移除此粒子系统。
		void Die();
		void MoveTo(float X, float Y);
		void OverrideColor(const char* emitter_name, Color& color);
		void OverrideExtraAdditiveDraw(boolean isEnable);
		void OverrideImage(Image image);
		void OverrideScale(float scale);
	};
	std::vector<TodParticleSystem> GetAllParticleSystem();
	PVZ::TodParticleSystem CreateParticleSystem(float X, float Y, int render_order, EffectType::EffectType type);
}
