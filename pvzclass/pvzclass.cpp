#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "ModLoader.h"

int main()
{
	ModLoader modloader;
	EventHandler handler;
	modloader.loadAsset(handler);

	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	EnableBackgroundRunning();

	modloader.loadDll(handler);
	handler.start();

	while (true)
	{
		handler.run(1);
		modloader.update();
	}

	handler.stop();
	modloader.freeAll();
	PVZ::QuitPVZ();
	return 0;
}
