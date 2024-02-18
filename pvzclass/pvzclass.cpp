#include "pvzclass.h"
#include "ModLoader.h"

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	std::cout << PVZ::Memory::processId << std::endl;
	PVZ::InitPVZ(pid);
	EnableBackgroundRunning();

	ModLoader modloader;
	modloader.loadAll();

	while (true)
	{
		modloader.update();
	}

	modloader.freeAll();
	PVZ::QuitPVZ();
	return 0;
}
