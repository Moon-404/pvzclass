#include "../PVZ.h"

PVZ::Board PVZ::SeedChooserScreen::GetBoard()
{
	return(PVZ::Board(Memory::ReadMemory<int>(BaseAddress + 0x0D14)));
}

PVZ::SeedChooserScreen::ChosenSeed PVZ::SeedChooserScreen::GetChosenSeed(int num)
{
	return(PVZ::SeedChooserScreen::ChosenSeed(BaseAddress + 0xA4 + num * 0x3C));
}
