#include "PreCompile.h"
#include "StatData.h"

float PlayerStatData::GetDamage()
{
	float Damage = (LUK * 4 + DEX) * ATK *((100.0f + AtkRate) / 100.0f) * ((100.0f + DmgRate + BossDmgRate) / 100.0f);
	
	std::random_device rnd;
	GameEngineRandom random = GameEngineRandom();
	random.SetSeed(rnd());
	float num = random.RandomFloat(0.5f, 1.5f);
	return Damage * num;
}

float MonsterStatData::GetDamage()
{
	return Damage;
}

float StatData::GetDamage()
{
	return 0.0f;
}
