#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	enum ProjectileDefType
	{
		PROJECTILEDEF_DAMAGE,
		PROJECTILEDEF_IMAGEROW
	};

	class ProjectileDefEvent
	{
	private:
		class DamagePart1 : public IntDLLEventTemplate<0x46E073, 7, 0, 0,
			INT32_MIN, REG_EDX, false, CONST_VAL(0), REG_ESI, CONST_VAL(PROJECTILEDEF_DAMAGE), REG_EDI>
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
				hookAddress = 0x46ECB0;
				rawlen = 7;
				BYTE code[] =
				{
					MOV_PTR_ESP_ADD_V_EUX(REG_EBP, 0x34),
					PUSH(1),
					PUSH_PTR_ESP_ADD_V(0x40),
					PUSH(PROJECTILEDEF_DAMAGE),
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
		class ImgRow : public IntDLLEventTemplate<0x46E6FA, 7, 0, 0,
			INT32_MIN, REG_EAX, false, CONST_VAL(0), CONST_VAL(0), CONST_VAL(PROJECTILEDEF_IMAGEROW), REG_ESI>
		{
		public:
			ImgRow(const char* str) : IntDLLEventTemplate() { Init(str); };
		};
		DamagePart1* part1;
		DamagePart2* part2;
		ImgRow* img;
	public:
		ProjectileDefEvent()
		{
			const char* str = "onProjectileDamageZombie";
			part1 = new DamagePart1(str);
			part2 = new DamagePart2(str);
			img = new ImgRow(str);
		}
		void end()
		{
			part1->end();
			part2->end();
			img->end();
		}
	};
}