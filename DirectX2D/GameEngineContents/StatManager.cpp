#include "PreCompile.h"
#include "StatManager.h"
#include "StatData.h"
#include "DamageIndicator.h"
#include "StatusBar.h"
#include "Player.h"

StatManager* StatManager::Inst;

StatManager::StatManager()
{
	Inst = this;
}

StatManager::~StatManager()
{

}

void StatManager::ChangeHp(std::shared_ptr<PlayerStatData> _Stat, float _Damage)
{
	_Stat->CurHp -= _Damage;

	float MaxHp = _Stat->MaxHp;
	float GaugeSizeX = StatusBar::Inst->HpGaugeSize.X;
	float ConvertedHp = -_Damage * (GaugeSizeX / MaxHp);
	StatusBar::Inst->ChangeHpGauge(ConvertedHp);
}

void StatManager::ChangeHp(std::shared_ptr<MonsterStatData> _Stat, float _Damage)
{
	_Stat->CurHp -= _Damage;
}

void StatManager::ChangeExp(float _Exp)
{
	std::shared_ptr<PlayerStatData> stat = Player::MainPlayer->GetStatData()->GetDynamic_Cast_This<PlayerStatData>();
	stat->CurExp += _Exp;

	float MaxExp = stat->MaxExp;
	float GaugeSizeX = ContentsCore::GetStartWindowSize().X;
	float ConvertedExp = _Exp * (GaugeSizeX / MaxExp);

	StatusBar::Inst->ChangeExpGauge(ConvertedExp);

	if (stat->CurExp > stat->MaxExp)
	{
		stat->CurExp = 0.0f;
		stat->CurLevel += 1;
		StatusBar::Inst->LevelUp(stat->CurLevel);
	}
	
}





