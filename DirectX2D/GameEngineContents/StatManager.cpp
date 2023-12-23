#include "PreCompile.h"
#include "StatManager.h"
#include "StatData.h"
#include "DamageIndicator.h"
#include "UI_Status.h"
#include "Player.h"

std::shared_ptr<StatManager> StatManager::Inst;

StatManager::StatManager()
{
}

StatManager::~StatManager()
{
}

void StatManager::ApplyDamage(float _Damage)
{
	PlayerStat->CurHp -= _Damage;

	float MaxHp = PlayerStat->MaxHp;
	float GaugeSizeX = PlayerStatus->HpGaugeSize.X;
	float ConvertedHp = -_Damage * (GaugeSizeX / MaxHp);
	PlayerStatus->ChangeHpGauge(ConvertedHp);
}

void StatManager::ResetHp()
{
	PlayerStat->CurHp = PlayerStat->MaxHp;
}

float StatManager::GetDamage()
{
	float Damage = (PlayerStat->LUK * 4 + PlayerStat->DEX) * PlayerStat->ATK * ((100.0f + PlayerStat->AtkRate) / 100.0f) * 
		((100.0f + PlayerStat->DmgRate + PlayerStat->BossDmgRate) / 100.0f);

	std::random_device rnd;
	GameEngineRandom random = GameEngineRandom();
	random.SetSeed(rnd());
	float num = random.RandomFloat(0.7f, 1.3f);
	return Damage * num;
}

std::vector<float> StatManager::GetDamage(int _HitCount, SkillType _Type)
{
	float SkillDamageRate = 0.0f;
	switch (_Type)
	{
	case SkillType::Body:
		break;
	case SkillType::FlashJump:
		break;
	case SkillType::LuckySeven:
		SkillDamageRate = PlayerStat->LuckySevenRate;
		break;
	case SkillType::ShowDown:
		SkillDamageRate = PlayerStat->ShowDownRate;
		break;
	default:
		break;
	}

	std::vector<float> DamageGroup;
	DamageGroup.reserve(_HitCount);
	for (int i = 0; i < _HitCount; i++)
	{
		float Damage = StatManager::GetDamage() * SkillDamageRate;
		DamageGroup.push_back(Damage);
	}
	return DamageGroup;
}

bool StatManager::IsDeath()
{
	if (PlayerStat->CurHp <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StatManager::ChangeExp(float _Exp)
{
	PlayerStat->CurExp += _Exp;

	float MaxExp = PlayerStat->MaxExp;
	float GaugeSizeX = ContentsCore::GetStartWindowSize().X;
	float ConvertedExp = _Exp * (GaugeSizeX / MaxExp);

	PlayerStatus->ChangeExpGauge(ConvertedExp);

	if (PlayerStat->CurExp >= PlayerStat->MaxExp)
	{
		PlayerStat->CurExp = 0.0f;
		PlayerStat->CurLevel += 1;
		PlayerStat->MaxExp += 100.0f;
		PlayerStatus->LevelUp(PlayerStat->CurLevel);
	}
}





