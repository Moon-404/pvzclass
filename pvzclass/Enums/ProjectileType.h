#pragma once
namespace ProjectileType
{

	enum ProjectileType
	{
		Pea,
		SnowPea,
		Cabbage,
		Melon,
		Puff,
		WinterMelon,
		FirePea,
		Star,
		Spike,
		Basketball,
		Kernel,
		CobCannon,
		Butter,
		ZombiePea,
	};

	constexpr ProjectileType Cactus = Spike;

	extern const char* ToString(ProjectileType projectilet);

}