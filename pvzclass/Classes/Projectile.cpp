#include "GameObject.hpp"

DWORD PVZ::Projectile::MemSize = 0x94;

PVZ::Projectile::Projectile(int indexoraddress)
{
	if (indexoraddress > 65535)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xC8) + indexoraddress * MemSize;
}

byte __asm__OnFire[]
{
	MOV_ECX(0),
	ONFIRE,
	RET,
};

void PVZ::Projectile::OnFire()
{
	SETARG(__asm__OnFire, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__OnFire));
}

byte __asm__Projectile__Remove[]
{
	MOV_EAX(0),
	PROJECTILE_REMOVE,
	RET
};

void PVZ::Projectile::Remove()
{
	SETARG(__asm__Projectile__Remove, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Projectile__Remove));
	return;
}