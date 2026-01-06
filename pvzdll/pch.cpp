// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

void init()
{
	PVZ::Memory::mainwindowhandle = PVZ::Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
	PVZ::Memory::Variable = PVZ::Memory::AllocMemory(4);
}

void beforeBoardUpdate()
{
	auto board = PVZ::GetBoard();
}

void pauseBoardUpdate()
{
	auto board = PVZ::GetBoard();
}

void afterBoardUpdate()
{
	auto board = PVZ::GetBoard();
}

void onAppUpdate(DWORD appAddress)
{
	auto app = PVZ::PVZApp(appAddress);
}

void onCoinCollect(DWORD coinAddress)
{
	auto coin = PVZ::Coin(coinAddress);
}

void onCoinCreate(DWORD coinAddress)
{
	auto coin = PVZ::Coin(coinAddress);
}

void onCoinRemove(DWORD coinAddress)
{
	auto coin = PVZ::Coin(coinAddress);
}

void onMousePointerClear(DWORD boardAddress)
{
	auto board = PVZ::Board(boardAddress);
}

int onDialogButtonDepress(int buttonId, int dialogId)
{
	return 0;
}

void onDialogDraw(DWORD graphics, Sexy::PDialog dialog)
{
}

void onDrawUITop(DWORD graphics)
{
}

void onDrawPlantReanim(DWORD plantAddress, DWORD animationAddress)
{
	auto plant = PVZ::Plant(plantAddress);
	auto anim = PVZ::Animation(animationAddress);
}

int onDrawZombieReanim(DWORD zombieAddress, DWORD animationAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
	auto anim = PVZ::Animation(animationAddress);
	return 0;
}

void onFatalError(EXCEPTION_POINTERS* lpEP)
{
	WriteStackTrace(lpEP, "stacktrace.txt");
}

int onRandomNumberGet(int number)
{
	return number;
}

void onNewGame()
{
	auto app = PVZ::GetPVZApp();
	app.LevelId = PVZLevel::Ice_Level;
}

void onPlantCreate(DWORD plantAddress)
{
	auto plant = PVZ::Plant(plantAddress);
}

void onPlantFromBank(DWORD plantAddress, int cardIndex)
{
	auto plant = PVZ::Plant(plantAddress);
	auto card = PVZ::GetBoard().GetCardSlot().GetCard(cardIndex);
}

int onPlantReload(DWORD plantAddress, int cd)
{
	auto plant = PVZ::Plant(plantAddress);
	return cd;
}

void onPlantShoot(DWORD plantAddress)
{
	auto plant = PVZ::Plant(plantAddress);
}

void onPlantRemove(DWORD plantAddress)
{
	auto plant = PVZ::Plant(plantAddress);
}

void onPeaOnFire(DWORD projectileAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
}

int onProjectileCollision(DWORD projectileAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
	if (projectile.Type == ProjectileType::Basketball) return 2;
	if (projectile.Type == ProjectileType::ZombiePea) return 1;
	return 0;
}

void onProjectileCreate(DWORD projectileAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
}

DWORD onProjectileHitPlant(DWORD projectileAddress, DWORD plantAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
	auto plant = PVZ::Plant(plantAddress);
	return plant.GetBaseAddress();
}

DWORD onProjectileHitZombie(DWORD projectileAddress, DWORD zombieAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
	auto zombie = PVZ::Zombie(zombieAddress);
	return zombie.GetBaseAddress();
}

int onProjectileRemove(DWORD projectileAddress)
{
	auto projectile = PVZ::Projectile(projectileAddress);
	return 0;
}

void onGameObjectsUpdate(DWORD boardAddress)
{
	auto board = PVZ::Board(boardAddress);
}

void onSeedCardClick(DWORD seedcardAddress)
{
	auto seedcard = PVZ::CardSlot::SeedCard(seedcardAddress);
}

bool onSeedPacketAllowedToPick(SeedType::SeedType type)
{
	return true;
}

void onToolClick()
{
	auto mousePointer = PVZ::GetBoard().GetMousePointer();
}

void onBossBungeeSpawn(DWORD zombieAddress)
{
	auto boss = PVZ::Zombie(zombieAddress);
	for (int i = 0; i < 3; i++)
	{
		// 这里控制行列
		auto zombie = Creator::CreateZombie(ZombieType::BungeeZombie, i, i);
		zombie.Height = zombie.Y - 30.0f;
		switch (i)
		{
		case 0:
			boss.FollowerZombieID0 = zombie.Id;
			break;
		case 1:
			boss.FollowerZombieID1 = zombie.Id;
			break;
		case 2:
			boss.FollowerZombieID2 = zombie.Id;
			break;
		default:
			break;
		}
	}
}

void onZombieBlast(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}

void onZombieButter(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}

void onZombieDecelerate(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}

void onZombieEat(DWORD zombieAddress, DWORD plantAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
	auto plant = PVZ::Plant(plantAddress);
}

void onZombieFroze(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}

int onZombieHit(DWORD zombieAddress, PVZ::DamageFlags type, DWORD amount)
{
	auto zombie = PVZ::Zombie(zombieAddress);
	return amount;
}

void onZombieHypnotize(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}

void onZombieRemove(DWORD zombieAddress)
{
	auto zombie = PVZ::Zombie(zombieAddress);
}
