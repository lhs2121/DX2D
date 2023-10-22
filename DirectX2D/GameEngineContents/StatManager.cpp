#include "PreCompile.h"
#include "StatManager.h"
#include "Player.h"
#include "StatData.h"
#include "ExpBar.h"
#include "StatusBar.h"
#include "DamageActor.h"

StatManager* StatManager::Inst;

StatManager::StatManager()
{
	Inst = this;
}

StatManager::~StatManager()
{

}

void StatManager::Start()
{
}

void StatManager::Update(float _Delta)
{

}

float StatManager::GetDamage(GameEngineCollision* _Col)
{
	std::shared_ptr<DamageActor> damageActor = _Col->GetActor()->GetDynamic_Cast_This<DamageActor>();

	GameEngineRandom rd = GameEngineRandom();
	std::random_device rnd;
	rd.SetSeed(rnd());

	float Dmg = damageActor->GetDamage();
	float Random = rd.RandomInt(-Dmg/10, Dmg/10);
	return Dmg + Random;
}

void StatManager::SetDamage(PlayerStatData* _StatData, DamageActor* _Weapon)
{
	float Dmg = (_StatData->LUK * 4 + _StatData->DEX) * _StatData->ATK *
		((100.0f + _StatData->AtkRate) / 100.0f) * ((100.0f + _StatData->DmgRate + _StatData->BossDmgRate) / 100.0f);

	_Weapon->SetDamage(Dmg);
}

void StatManager::ChangeHp(MonsterStatData* _StatData, float _HpValue)
{
	_StatData->CurHp += _HpValue;
}

void StatManager::ChangeHp(PlayerStatData* _StatData, float _HpValue)
{
	_StatData->CurHp += _HpValue;

	float MaxHp = _StatData->MaxHp;
	float GaugeSizeX = StatusBar::Inst->HpGaugeSizeX;
	float ConvertedHp = _HpValue * (GaugeSizeX / MaxHp);
	StatusBar::Inst->ChangeHpGauge(ConvertedHp);
}

void StatManager::ChangeMp(PlayerStatData* _StatData, float _MpValue)
{
	_StatData->CurMp += _MpValue;

	float MaxMp = _StatData->MaxMp;
	float GaugeSizeX = StatusBar::Inst->MpGaugeSizeX;
	float ConvertedMp = _MpValue * (GaugeSizeX / MaxMp);
	StatusBar::Inst->ChangeHpGauge(ConvertedMp);
}

void StatManager::ChangeExp(PlayerStatData* _StatData, float _ExpValue)
{
	_StatData->CurExp += _ExpValue;

	float MaxExp = _StatData->MaxExp;
	float GaugeSizeX = 1920.0f;
	float ConvertedExp = _ExpValue * (GaugeSizeX / MaxExp);

	ExpBar::Inst->ChangeExpGauge(ConvertedExp);

	if (_StatData->CurExp >= _StatData->MaxExp)
	{
		_StatData->CurExp = 0;
		_StatData->MaxExp += 10;
		_StatData->CurLevel += 1;
		ExpBar::Inst->ExpGaugeReset();
	}
}
