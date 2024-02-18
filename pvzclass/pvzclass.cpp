#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "ModLoader.h"

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	EnableBackgroundRunning();

	EventHandler handler;
	ModLoader modloader;
	modloader.loadAll(handler);
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
