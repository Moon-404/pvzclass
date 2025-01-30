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
		void MoveTo(const float X, const float Y);
		void OverrideColor(const char* emitter_name, const Color& color);
		void OverrideExtraAdditiveDraw(const boolean isEnable);
		void OverrideImage(Image image);
		void OverrideScale(const float scale);
	};
	std::vector<TodParticleSystem> GetAllParticleSystem();
	PVZ::TodParticleSystem CreateParticleSystem(const float X, const float Y, const int render_order, const EffectType::EffectType type);
}
