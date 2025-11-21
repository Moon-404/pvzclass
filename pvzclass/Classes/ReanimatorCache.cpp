#include "ReanimatorCache.hpp"

void PVZ::ReanimatorCache::SetMemSize(DWORD zombie_num)
{
	PVZ::Memory::WriteMemory<int>(0x452B40, 256 + (zombie_num << 2));

	PVZ::Memory::WriteMemory<int>(0x46FDC7, 252 + (zombie_num << 2));
	PVZ::Memory::WriteMemory<int>(0x470056, 252 + (zombie_num << 2));

	byte __asm__inject[]
	{
		PUSHDWORD((zombie_num << 2) - 100),
		PUSH(0),
		PUSH_EDX,
		CALC_PTR_ESP(CALC_ADD, 0),
		INVOKE(0x626020),
		ADD_ESP(0x0C),
		MOV_EUX_PTR_ADDR(REG_EAX, 0x6AF938),
		MOV_PTR_EUX_ADD__EVX(REG_EDX, REG_EAX, 252 + (zombie_num << 2)),
		POP_EUX(REG_EDI),
		RET
	};
	Memory::WriteArray(0x0046FE97, STRING(__asm__inject));
}