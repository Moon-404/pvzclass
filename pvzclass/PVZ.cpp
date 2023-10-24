﻿#include "PVZ.h"


PVZ::PVZ(DWORD pid)
{
	Memory::processId = pid;
	Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	Memory::mainwindowhandle = Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
	Memory::Variable = Memory::AllocMemory();

	DEBUG_EVENT debugEvent;
	DebugActiveProcess(Memory::processId);
	WaitForDebugEvent(&debugEvent, -1);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	DebugActiveProcessStop(PVZ::Memory::processId);

	Memory::mainThreadId = debugEvent.dwThreadId;
	Memory::hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
}

PVZ::~PVZ()
{
	CloseHandle(Memory::hProcess);
	Memory::FreeMemory(Memory::Variable);
}

#pragma region background methods

const char* PVZ::__get_Version()
{
	return "beta_1.15.0.1.231024";
}

PVZVersion::PVZVersion PVZ::__get_GameVersion()
{
	int ver = Memory::ReadMemory<int>(0x552013);
	switch (ver)
	{
	case 0xC35EDB74:
		return PVZVersion::V1_0_0_1051;
	case 0x86831977:
		return PVZVersion::V1_2_0_1065;
	case 0x3B000001:
		return PVZVersion::V1_2_0_1073;
	case 0x878B0000:
		return PVZVersion::CHINESE_ENHANCED;
	case 0xA48F:
		return PVZVersion::CHINESE_VISCOSITY;
	default:
		return PVZVersion::UnknowOrNotPVZ;
	}
}

double PVZ::__get_MusicVolume()
{
	return Memory::ReadMemory<double>(PVZ_BASE + 0xD0);
}

void PVZ::__set_MusicVolume(double value)
{
	Memory::WriteMemory<double>(PVZ_BASE + 0xD0, value);
	SETARG(__asm__set_MusicVolume, 1) = PVZ_BASE;
	Memory::Execute(STRING(__asm__set_MusicVolume));
}

double PVZ::__get_SoundFXVolume()
{
	return Memory::ReadMemory<double>(PVZ_BASE + 0xD8);
}

void PVZ::__set_SoundFXVolume(double value)
{
	Memory::WriteMemory<double>(PVZ_BASE + 0xD8, value);
	SETARG(__asm__set_MusicVolume, 1) = PVZ_BASE;
	Memory::Execute(STRING(__asm__set_MusicVolume));
}

SceneType::SceneType PVZ::__get_LevelScene()
{
	return Memory::ReadMemory<SceneType::SceneType>(BaseAddress + 0x554C);
}

void PVZ::__set_LevelScene(SceneType::SceneType value)
{
	Memory::WriteMemory<SceneType::SceneType>(BaseAddress + 0x554C, value);
	SETARG(__asm__set__LevelScene, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__set__LevelScene));
}

int PVZ::__get_WaveCount()
{
	return Memory::ReadMemory<int>(BaseAddress + 0x5564);
}

void PVZ::__set_WaveCount(int value)
{
	if (value >= 0 && value <= WaveCount)
	{
		Memory::WriteMemory<int>(BaseAddress + 0x5564, value);
		Memory::WriteMemory<int>(BaseAddress + 0x5610, value * 150 / WaveCount);
	}
}

#pragma endregion

#pragma region methods

void PVZ::Memory::InjectDll(LPCSTR dllname)
{
	int Address = PVZ::Memory::AllocMemory();
	SETARG(__asm__InjectDll, 1) = Address + 0x13;
	lstrcpyA((LPSTR)(__asm__InjectDll + 0x13), dllname);
	WriteArray<byte>(Address, STRING(__asm__InjectDll));
	WriteMemory<byte>(0x552014, 0xFE);
	CreateThread(Address);
	WriteMemory<byte>(0x552014, 0xDB);
	FreeMemory(Address);
}

SPT<PVZ::PVZApp> PVZ::GetPVZApp()
{
	return MKS<PVZApp>(PVZ::Memory::ReadMemory<DWORD>(0x6A9EC0));
}

SPT<PVZ::Lawn> PVZ::GetLawn()
{
	return MKS<Lawn>(BaseAddress);
}

SPT<PVZ::Icetrace> PVZ::GetIcetrace()
{
	return MKS<Icetrace>(BaseAddress);
}

SPT<PVZ::Wave> PVZ::GetWave(int index)
{
	if (index >= 0 && index <= WaveCount)
		return MKS<Wave>(BaseAddress + 0x6B4 + index * 200);
	else
		return NULL;
}

void PVZ::GetZombieSeed(ZombieType::ZombieType* ztypes)
{
	SPT<PVZ::Board> board = this->GetBoard();
	if (board != nullptr)
		board->GetZombieAllowed(ztypes);
}

void PVZ::Earthquake(int horizontalAmplitude, int verticalAmplitude, int duration)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5540, duration);
	Memory::WriteMemory<int>(BaseAddress + 0x5544, horizontalAmplitude);
	Memory::WriteMemory<int>(BaseAddress + 0x5548, verticalAmplitude);
}

void PVZ::Assault(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5574, countdown);
}

void PVZ::Win()
{
	SETARG(__asm__Win, 1) = BaseAddress;
	if (LevelId > 0 && LevelId < 16)
	{
		if (GameState == PVZGameState::Playing)Memory::Execute(STRING(__asm__Win));
	}
	else Memory::Execute(STRING(__asm__Win));
}

void PVZ::Lose()
{
	if (LevelId == PVZLevel::Zombiguarium || (LevelId >= 61 && LevelId <= 70))
	{
		SETARG(__asm__Lose, 3) = BaseAddress;
		Memory::Execute(STRING(__asm__Lose));
	}
	else
		this->GameState = PVZGameState::Losing;
}

void PVZ::Bell(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5750, countdown);
}

SPT<PVZ::Mouse> PVZ::GetMouse()
{
	return MKS<Mouse>(Memory::ReadPointer(0x6A9EC0, 0x320));
}

std::vector<SPT<PVZ::Zombie>> PVZ::GetAllZombies()
{
	std::vector<SPT<Zombie>> zombies;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x94);
	for (int i = 0; i < maxnum; i++) 
	{
		if (!Memory::ReadPointer(BaseAddress + 0x90, 0xEC + 0x15C * i))
			zombies.push_back(MKS<PVZ::Zombie>(i));
	}
	return zombies;
}

std::vector<SPT<PVZ::Plant>> PVZ::GetAllPlants()
{
	std::vector<SPT<Plant>> plants;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xB0);
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadMemory<byte>(Memory::ReadMemory<int>(BaseAddress + 0xAC) + 0x141 + 0x14C * i))
			plants.push_back(MKS<PVZ::Plant>(i));
	}
	return plants;
}

std::vector<SPT<PVZ::Projectile>> PVZ::GetAllProjectile()
{
	std::vector<SPT<Projectile>> projectiles;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0xC8, 0x50 + 0x94 * i))
			projectiles.push_back(MKS<PVZ::Projectile>(i));
	}
	return projectiles;
}

std::vector<SPT<PVZ::Coin>> PVZ::GetAllCoins()
{
	std::vector<SPT<Coin>> coins;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xE8);
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0xE4, 0x38 + 0xD8 * i))
			coins.push_back(MKS<PVZ::Coin>(i));
	}
	return coins;
}

std::vector<SPT<PVZ::Lawnmover>> PVZ::GetAllLawnmovers()
{
	std::vector<SPT<Lawnmover>> lawnmovers;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x104);
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0x100, 0x30 + 0x48 * i))
			lawnmovers.push_back(MKS<PVZ::Lawnmover>(i));
	}
	return lawnmovers;
}

std::vector<SPT<PVZ::Griditem>> PVZ::GetAllGriditems()
{
	std::vector<SPT<Griditem>> griditems;
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x120);
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0x11C, 0x20 + 0xEC * i))
			griditems.push_back(MKS<PVZ::Griditem>(i));
	}
	return griditems;
}

SPT<PVZ::MousePointer> PVZ::GetMousePointer()
{
	return MKS<MousePointer>(BaseAddress);
}

SPT<PVZ::Board> PVZ::GetBoard()
{
	int address = BaseAddress;
	return(address == 0 ? nullptr : MKS<Board>(BaseAddress));
}

SPT<PVZ::SeedChooserScreen> PVZ::GetSeedChooserScreen()
{
	int address = Memory::ReadPointer(0x6A9EC0, 0x774);
	return(address == 0 ? nullptr : MKS<SeedChooserScreen>(BaseAddress));
}

SPT<PVZ::Caption> PVZ::GetCaption()
{
	return MKS<Caption>(BaseAddress);
}

SPT<PVZ::CardSlot> PVZ::GetCardSlot()
{
	return MKS<CardSlot>(BaseAddress);
}

SPT<PVZ::ZenGarden> PVZ::GetZenGarden()
{
	return MKS<ZenGarden>(Memory::ReadPointer(0x6A9EC0, 0x81C));
}

SPT<PVZ::PlantDefinition> PVZ::GetPlantDefinition(PlantType::PlantType type)
{
	return MKS<PlantDefinition>(type);
}

SPT<PVZ::ZombieDefinition> PVZ::GetZombieDefinition(ZombieType::ZombieType type)
{
	return MKS<ZombieDefinition>(type);
}

SPT<PVZ::ProjectileDefinition> PVZ::GetProjectileDefinition(ProjectileType::ProjectileType type)
{
	return MKS<ProjectileDefinition>(type);
}

SPT<PVZ::ChallengeDefinition> PVZ::GetChallengeDefinition(PVZLevel::PVZLevel mode)
{
	return MKS<ChallengeDefinition>(mode);
}

SPT<PVZ::Miscellaneous> PVZ::GetMiscellaneous()
{
	return MKS<Miscellaneous>(BaseAddress);
}

SPT<PVZ::SaveData> PVZ::GetSaveData()
{
	return MKS<SaveData>(Memory::ReadPointer(0x6A9EC0, 0x82C));
}

SPT<PVZ::Music> PVZ::GetMusic()
{
	return MKS<Music>(Memory::ReadPointer(0x6A9EC0, 0x83C));
}

#pragma endregion

int PVZ::GameObject::GetBaseAddress()
{
	return this->BaseAddress;
}
