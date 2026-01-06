#include "CutScene.hpp"

PVZ::CutScene::CutScene(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x15C);
}

void PVZ::CutScene::PlaceStreetZombie(ZombieType::ZombieType type, int x, int y)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(y)
		.push(x)
		.push(type)
		.push(BaseAddress)
		.invoke(0x439140)
		.ret()
	);
}
