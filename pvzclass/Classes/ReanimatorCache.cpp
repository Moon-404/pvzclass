#include "ReanimatorCache.hpp"

void PVZ::ReanimatorCache::SetMemSize(byte zombie_num, DWORD lawnmower_num)
{
	PVZ::Memory::WriteMemory<int>(0x452B40, 232 + ((zombie_num + lawnmower_num) << 2));

	PVZ::Memory::WriteMemory<int>(0x46FDC7, 228 + ((zombie_num + lawnmower_num) << 2));
	PVZ::Memory::WriteMemory<int>(0x470058, 228 + ((zombie_num + lawnmower_num) << 2));

	PVZ::Memory::WriteMemory<byte>(0x46FF7D, zombie_num);
	PVZ::Memory::WriteMemory<int>(0x46FF61, lawnmower_num);

	PVZ::Memory::WriteMemory<int>(0x46FF80, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x403168, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x403179, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x403184, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x470174, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x470185, 228 + (lawnmower_num << 2));
	PVZ::Memory::WriteMemory<int>(0x47018F, 228 + (lawnmower_num << 2));

	byte __asm__inject[]
	{
		PUSH_EDX,
		PUSHDWORD(((zombie_num + lawnmower_num) << 2) - 124),
		PUSH(0),
		PUSH_EDX,
		CALC_PTR_ESP(CALC_ADD, 0x160),
		INVOKE(0x626020),
		ADD_ESP(0x0C),
		POP_EUX(REG_EDX),
		MOV_EUX_PTR_ADDR(REG_EAX, 0x6A9F38),
		MOV_PTR_EUX_ADD__EVX(REG_EDX, REG_EAX, 228 + ((zombie_num + lawnmower_num) << 2)),
		POP_EUX(REG_EDI),
		RET
	};
	Memory::WriteArray(0x0046FE97, STRING(__asm__inject));
}