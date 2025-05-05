#include "Definition.hpp"

PVZ::PlantDefinition::PlantDefinition(SeedType::SeedType type)
{
	BaseAddress = 0x69F2B0 + 0x24 * type;
}

PVZ::PlantDefinition PVZ::GetPlantDefinition(SeedType::SeedType type)
{
	return PlantDefinition(type);
}

PVZ::ZombieDefinition::ZombieDefinition(ZombieType::ZombieType type)
{
	BaseAddress = 0x69DA80 + 0x1C * type;
}

PVZ::ZombieDefinition PVZ::GetZombieDefinition(ZombieType::ZombieType type)
{
	return ZombieDefinition(type);
}

PVZ::ProjectileDefinition::ProjectileDefinition(ProjectileType::ProjectileType type)
{
	BaseAddress = 0x69F1C0 + 0xC * type;
}

PVZ::ProjectileDefinition PVZ::GetProjectileDefinition(ProjectileType::ProjectileType type)
{
	return ProjectileDefinition(type);
}

PVZ::ChallengeDefinition::ChallengeDefinition(PVZLevel::PVZLevel mode)
{
	BaseAddress = 0x6A2B88 + 0x18 * mode;
}

PVZ::ChallengeDefinition PVZ::GetChallengeDefinition(PVZLevel::PVZLevel mode)
{
	return ChallengeDefinition(mode);
}