#include "LawnMower.hpp"

DWORD PVZ::Lawnmover::MemSize = 0x48;

PVZ::LawnMower::LawnMower(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x100) + indexoraddress * MemSize;
}

PVZ::Animation PVZ::LawnMower::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x1C);
	return ((ID_RANK(ID) == 0) ? INVALID_BASEADDRESS : Animation(ID_INDEX(ID)));
}

byte __asm__Lawnmover_Die[]
{
	MOV_EUX(REG_EAX, 0),
	LAWNMOVER_DIE,
	RET,
};

void PVZ::LawnMower::Die()
{
	SETARG(__asm__Lawnmover_Die, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Lawnmover_Die));
	return;
}

void PVZ::LawnMower::Update()
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(this->GetBaseAddress())
		.invoke(0x4586E0)
		.ret()
	);
}

void PVZ::LawnMower::UpdatePool()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EDI, this->GetBaseAddress())
		.invoke(0x4581E0)
		.ret()
	);
}