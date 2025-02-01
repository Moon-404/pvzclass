#include "../pvzclass/pvzclass.h"
#include "../pvzclass/Events/Events.h"

int main()
{
	PVZ::Memory::localExecute = false;
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	while (PVZ::GetPVZApp()->GameState != PVZGameState::MainMenu) Sleep(10);
	PVZ::Memory::immediateExecute = true;
	PVZ::Memory::InjectDll("pvzdll.dll");
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();
	DisableInitialLawnmover();
	DisableIceLevelFailSound();
	DrawPlantReanimEvent();
	PVZ::QuitPVZ();
	return 0;
}
