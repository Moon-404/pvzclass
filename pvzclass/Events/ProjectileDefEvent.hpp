#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	enum ProjDmgType
	{
		DAMAGE_SINGULAR,
		DAMAGE_SPLASH_PRIMARY,
		DAMAGE_SPLASH_SECONDARY
	};

	class ProjectileDamageZombieEvent
	{
	private:
		class DamagePart1 : public IntDLLEventTemplate<0x46E073, 7, 0, 0,
			INT32_MIN, REG_EDX, false, CONST_VAL(0), CONST_VAL(DAMAGE_SINGULAR), REG_ESI, REG_EDI>
		{
		public:
			DamagePart1(const char* str) : IntDLLEventTemplate() { Init(str); };
		};
		class DamagePart2 : public DLLEvent
		{
		public: 
			DamagePart2(const char* str)
			{
				int procAddress = PVZ::Memory::GetProcAddress(str);
				hookAddress = 0x46D468;
				rawlen = 5;
				BYTE code[] =
				{
					PUSH_PTR_ESP_ADD_V(0x34),

					CALC_PTR_ESP_ADD_V_EUX(CALC_CMP, REG_ESI, 0x40),
					JNZ(4),
					PUSH(DAMAGE_SPLASH_PRIMARY),
					JMP(2),
					PUSH(DAMAGE_SPLASH_SECONDARY),

					PUSH_PTR_ESP_ADD_V(0x44),
					PUSH_EDI,
					INVOKE(procAddress),
					ADD_ESP(0x0C),

					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),
					POPAD,
					MOV_EAX(0x46D3EE),
					JMP_REG32(REG_EAX)
				};
				start(STRING(code));
			}
		};
		DamagePart1* part1;
		DamagePart2* part2;
	public:
		ProjectileDamageZombieEvent()
		{
			const char* str = "onProjectileDamageZombie";
			part1 = new DamagePart1(str);
			part2 = new DamagePart2(str);
		}
		void end()
		{
			part1->end();
			part2->end();
		}
	};
}