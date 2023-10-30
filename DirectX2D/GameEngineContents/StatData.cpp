#include "PreCompile.h"
#include "StatData.h"

float StatDataPlayer::GetDamage()
{
	float Damage = (LUK * 4 + DEX) * ATK * ((100.0f + AtkRate) / 100.0f) * ((100.0f + DmgRate + BossDmgRate) / 100.0f);

	std::random_device rnd;
	GameEngineRandom random = GameEngineRandom();
	random.SetSeed(rnd());
	float num = random.RandomFloat(0.7f, 1.3f);
	return Damage * num;
}

std::vector<float> StatDataPlayer::GetDamage(int _HitCount, SkillType _Type)
{
	float SkillDamageRate = 0.0f;
	switch (_Type)
	{
	case SkillType::Body:
		break;
	case SkillType::FlashJump:
		break;
	case SkillType::LuckySeven:
		SkillDamageRate = LuckySevenRate;
		break;
	case SkillType::ShowDown:
		SkillDamageRate = ShowDownRate;
		break;
	default:
		break;
	}


	std::vector<float> DamageGroup;
	DamageGroup.reserve(_HitCount);
	for (int i = 0; i < _HitCount; i++)
	{
		float Damage = StatDataPlayer::GetDamage() * SkillDamageRate;
		DamageGroup.push_back(Damage);
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
	CurHp = _Other.CurHp;
	MaxHp = _Other.MaxHp;
	DEF = _Other.DEF;
	CurMp = _Other.CurMp;
	MaxMp = _Other.MaxMp;
	CurExp = _Other.CurExp;
	MaxExp = _Other.MaxExp;
	CurMoney = _Other.CurMoney;
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
