#include "Widgets/GameSelector.hpp"

void PVZ::GameSelector::SetMemSize(uint32_t NewSize)
{
	PVZ::Memory::WriteMemory<uint32_t>(0x44F929, NewSize);
}
