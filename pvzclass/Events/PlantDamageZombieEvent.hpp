#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	enum PlantDamageType
	{
		PLANTDAMAGETYPE_RETALIATE,
		PLANTDAMAGETYPE_BOWLING,
		PLANTDAMAGETYPE_CHOMPER,
		PLANTDAMAGETYPE_AOE,
	};

	class PlantDamageZombieEvent
	{
	public:
		class PZDamageInfo
		{
			PVZ::Zombie zombie;
			PVZ::Plant plant;
			PVZ::DamageFlags flags;
			int damage;
			PlantDamageType type;
			PZDamageInfo(PVZ::Zombie zombie, PVZ::Plant plant, PVZ::DamageFlags flags, int damage, PlantDamageType type)
				: zombie(zombie), plant(plant), flags(flags), damage(damage), type(type) {}
		};
	private:
		class Part1 : public DLLEvent
		{
		public:
			Part1(int address)
			{
				hookAddress = 0x526D81;
				rawlen = 5;
				int tmp = PVZ::Memory::Variable;
				BYTE code[] =
				{
					PUSH_EAX,
					PUSH(0x14),
					INVOKE(0x61C130),
					MOV_EUX_EVX(REG_EBP, REG_EAX),
					POP_EUX(REG_EAX),

					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_ESI, 0),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EDI, 4),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 8),
					MOV_REG32_PTR_ESP_ADD_V(REG_EAX, 0x20),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 0x0C),
					MOV_PTR_EUX_ADD_V(REG_EBP, 0x10, PLANTDAMAGETYPE_RETALIATE),

					PUSH_EBP,
					INVOKE(address),
					ADD_ESP(4),
					MOV_PTR_ADDR_EUX(REG_EBP, tmp),
					POPAD,
					PUSH_EBP,
					MOV_EUX_PTR_ADDR(REG_EBP, tmp),

					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 0x0C),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),

					MOV_EUX_PTR_EVX_ADD_V(REG_ESI, REG_EBP, 0),
					MOV_EUX_PTR_EVX_ADD_V(REG_EDI, REG_EBP, 4),
					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 8),

					POP_EUX(REG_EBP),
					PUSH_PTR(tmp),
					INVOKE(0x61C19A),
					JMP(1)
				};
				start(STRING(code));
			}
			Part1(const char* str) : Part1(PVZ::Memory::GetProcAddress(str)) {}
		};
		class Part2 : public DLLEvent
		{
		public:
			Part2(int address)
			{
				hookAddress = 0x462FC3;
				rawlen = 5;
				int tmp = PVZ::Memory::Variable;
				BYTE code[] =
				{
					PUSH_EAX,
					PUSH(0x14),
					INVOKE(0x61C130),
					MOV_EUX_EVX(REG_EBP, REG_EAX),
					POP_EUX(REG_EAX),

					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_ESI, 0),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EDI, 4),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 8),
					MOV_REG32_PTR_ESP_ADD_V(REG_EAX, 0x20),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 0x0C),
					MOV_PTR_EUX_ADD_V(REG_EBP, 0x10, PLANTDAMAGETYPE_BOWLING),

					PUSH_EBP,
					INVOKE(address),
					ADD_ESP(4),
					MOV_PTR_ADDR_EUX(REG_EBP, tmp),
					POPAD,
					PUSH_EBP,
					MOV_EUX_PTR_ADDR(REG_EBP, tmp),

					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 0x0C),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),

					MOV_EUX_PTR_EVX_ADD_V(REG_ESI, REG_EBP, 0),
					MOV_EUX_PTR_EVX_ADD_V(REG_EDI, REG_EBP, 4),
					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 8),

					POP_EUX(REG_EBP),
					PUSH_PTR(tmp),
					INVOKE(0x61C19A),
					JMP(1)
				};
				start(STRING(code));
			}
			Part2(const char* str) : Part2(PVZ::Memory::GetProcAddress(str)) {}
		};
		class Part3 : public DLLEvent
		{
		public:
			Part3(int address)
			{
				hookAddress = 0x4614E0;
				rawlen = 5;
				int tmp = PVZ::Memory::Variable;
				BYTE code[] =
				{
					PUSH_EAX,
					PUSH(0x14),
					INVOKE(0x61C130),
					MOV_EUX_EVX(REG_EBP, REG_EAX),
					POP_EUX(REG_EAX),

					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_ESI, 0),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EDI, 4),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 8),
					MOV_REG32_PTR_ESP_ADD_V(REG_EAX, 0x20),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 0x0C),
					MOV_PTR_EUX_ADD_V(REG_EBP, 0x10, PLANTDAMAGETYPE_CHOMPER),

					PUSH_EBP,
					INVOKE(address),
					ADD_ESP(4),
					MOV_PTR_ADDR_EUX(REG_EBP, tmp),
					POPAD,
					PUSH_EBP,
					MOV_EUX_PTR_ADDR(REG_EBP, tmp),

					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 0x0C),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),

					MOV_EUX_PTR_EVX_ADD_V(REG_ESI, REG_EBP, 0),
					MOV_EUX_PTR_EVX_ADD_V(REG_EDI, REG_EBP, 4),
					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 8),

					POP_EUX(REG_EBP),
					PUSH_PTR(tmp),
					INVOKE(0x61C19A),
					JMP(1)
				};
				start(STRING(code));
			}
			Part3(const char* str) : Part3(PVZ::Memory::GetProcAddress(str)) {}
		};
		class Part4 : public DLLEvent
		{
		public:
			Part4(int address)
			{
				hookAddress = 0x4607B2;
				rawlen = 5;
				int tmp = PVZ::Memory::Variable;
				BYTE code[] =
				{
					PUSH_EAX,
					PUSH(0x14),
					INVOKE(0x61C130),
					MOV_EUX_EVX(REG_EBP, REG_EAX),
					POP_EUX(REG_EAX),

					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_ESI, 0),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EDI, 4),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 8),
					MOV_REG32_PTR_ESP_ADD_V(REG_EAX, 0x20),
					MOV_PTR_EUX_ADD_V_EVX(REG_EBP, REG_EAX, 0x0C),
					MOV_PTR_EUX_ADD_V(REG_EBP, 0x10, PLANTDAMAGETYPE_AOE),

					PUSH_EBP,
					INVOKE(address),
					ADD_ESP(4),
					MOV_PTR_ADDR_EUX(REG_EBP, tmp),
					POPAD,
					PUSH_EBP,
					MOV_EUX_PTR_ADDR(REG_EBP, tmp),

					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 0x0C),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),

					MOV_EUX_PTR_EVX_ADD_V(REG_ESI, REG_EBP, 0),
					MOV_EUX_PTR_EVX_ADD_V(REG_EDI, REG_EBP, 4),
					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EBP, 8),

					POP_EUX(REG_EBP),
					PUSH_PTR(tmp),
					INVOKE(0x61C19A),
					JMP(1)
				};
				start(STRING(code));
			}
			Part4(const char* str) : Part4(PVZ::Memory::GetProcAddress(str)) {}
		};
		class Part5 : public DLLEvent
		{
		public:
			Part5(int address)
			{
				hookAddress = 0x45EE22;
				rawlen = 5;
				int tmp = PVZ::Memory::Variable;
				BYTE code[] =
				{
					PUSH_EAX,
					PUSH(0x14),
					INVOKE(0x61C130),
					MOV_EUX_EVX(REG_EDX, REG_EAX),
					POP_EUX(REG_EAX),

					MOV_PTR_EUX_ADD_V_EVX(REG_EDX, REG_ESI, 0),
					MOV_PTR_EUX_ADD_V_EVX(REG_EDX, REG_EDI, 4),
					MOV_PTR_EUX_ADD_V_EVX(REG_EDX, REG_EBP, 8),
					MOV_REG32_PTR_ESP_ADD_V(REG_EAX, 0x20),
					MOV_PTR_EUX_ADD_V_EVX(REG_EDX, REG_EAX, 0x0C),
					MOV_PTR_EUX_ADD_V(REG_EDX, 0x10, PLANTDAMAGETYPE_AOE),

					PUSH_EDX,
					INVOKE(address),
					ADD_ESP(4),
					MOV_PTR_ADDR_EUX(REG_EDX, tmp),
					POPAD,
					PUSH_EDX,
					MOV_EUX_PTR_ADDR(REG_EDX, tmp),

					MOV_EUX_PTR_EVX_ADD_V(REG_EAX, REG_EDX, 0x0C),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0),

					MOV_EUX_PTR_EVX_ADD_V(REG_ESI, REG_EDX, 0),
					MOV_EUX_PTR_EVX_ADD_V(REG_EDI, REG_EDX, 4),
					MOV_EUX_PTR_EVX_ADD_V(REG_EBP, REG_EDX, 8),

					POP_EUX(PUSH_EDX),
					PUSH_PTR(tmp),
					INVOKE(0x61C19A),
					JMP(1)
				};
				start(STRING(code));
			}
			Part5(const char* str) : Part5(PVZ::Memory::GetProcAddress(str)) {}
		};
		Part1* spikerock1;
		Part2* bowling;
		Part3* chomper;
		Part4* squash;
		Part5* rowarea;
	public:
		PlantDamageZombieEvent()
		{
			const char* str = "onPlantDamageZombie";
			spikerock1 = new Part1(str);
			bowling = new Part2(str);
			chomper = new Part3(str);
			squash = new Part4(str);
			rowarea = new Part5(str);
		}
		PlantDamageZombieEvent(int address)
		{
			spikerock1 = new Part1(address);
			bowling = new Part2(address);
			chomper = new Part3(address);
			squash = new Part4(address);
			rowarea = new Part5(address);
		}
		void end()
		{
			spikerock1->end();
			bowling->end();
			chomper->end();
			squash->end();
		}
	};
}