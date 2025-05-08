#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	class ProjectileDefEvent
	{
	private:
		class Part1 : public IntDLLEventTemplate<0x46E073, 7, 0, 0,
			INT32_MIN, REG_EDX, false, CONST_VAL(0), REG_ESI, REG_EDI>
		{
		public:
			Part1(const char* str) : IntDLLEventTemplate() { Init(str); };
		};
		class Part2 : public DLLEvent
		{
		public: 
			Part2(const char* str)
			{
				int procAddress = PVZ::Memory::GetProcAddress(str);
				hookAddress = 0x46ECB0;
				rawlen = 7;
				BYTE code[] =
				{
					MOV_PTR_ESP_ADD_V_EUX(REG_EBP, 0x34),
					PUSH(1),
					PUSH_PTR_ESP_ADD_V(0x40),
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
		Part1* part1;
		Part2* part2;
	public:
		ProjectileDefEvent()
		{
			part1 = new Part1("onProjectileDamageZombie");
			part2 = new Part2("onProjectileDamageZombie");
		}
		void end()
		{
			part1->end();
			part2->end();
		}
	};
}