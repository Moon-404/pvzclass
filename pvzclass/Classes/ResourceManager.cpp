#include "ResourceManager.hpp"

namespace PVZ
{
	SPT<ResourceManager> GetResourceManager()
	{
		return ResourceManager(Memory::ReadPointer(0x6A9EC0, 0x634));
	}
	SPT<PVZApp> ResourceManager::GetPVZApp()
	{
		return PVZApp(Memory::ReadMemory<DWORD>(BaseAddress + 0x58));
	}
}