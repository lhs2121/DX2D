#include "PreCompile.h"
#include "StatData.h"

float StatData::GetDamage()
{
	return 0.0f;
}

std::vector<float> StatData::GetDamage(int _HitCount)
{
	return {0.0f};
}


float StatDataPlayer::GetDamage()
{
	float Damage = (LUK * 4 + DEX) * ATK * ((100.0f + AtkRate) / 100.0f) * ((100.0f + DmgRate + BossDmgRate) / 100.0f);

	std::random_device rnd;
	GameEngineRandom random = GameEngineRandom();
	random.SetSeed(rnd());
	float num = random.RandomFloat(0.7f, 1.3f);
	return Damage * num;
}

std::vector<float> StatDataPlayer::GetDamage(int _HitCount)
{
	std::vector<float> DamageGroup;
	DamageGroup.reserve(_HitCount);
	for (int i = 0; i < _HitCount; i++)
	{
		DamageGroup.push_back(StatDataPlayer::GetDamage());
	}
	return DamageGroup;
}

float StatDataMonster::GetDamage()
{
	return BodyDamage;
}

StatDataPlayer::StatDataPlayer(const StatDataPlayer& _Other)
{
	CurLevel = _Other.CurLevel;
	MaxLevel = _Other.MaxLevel;
	CurHp = _Other.CurHp;
	MaxHp = _Other.MaxHp;
	DEF = _Other.DEF;
	CurMp = _Other.CurMp;
	MaxMp = _Other.MaxMp;
	CurExp = _Other.CurExp;
	MaxExp = _Other.MaxExp;
	CurMoney = _Other.CurMoney;
	MaxMoney = _Other.MaxMoney;
	STR = _Other.STR;
	DEX = _Other.DEX;
	INT = _Other.INT;
	LUK = _Other.LUK;
	ATK = _Other.ATK;
	AtkRate = _Other.AtkRate;
	DmgRate = _Other.DmgRate;
	BossDmgRate = _Other.BossDmgRate;
	CriDmg = _Other.CriDmg;
	CriRate = _Other.CriRate;

}
