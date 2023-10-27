#include "PreCompile.h"
#include "StatManager.h"
#include "StatData.h"
#include "DamageIndicator.h"
#include "UI_Status.h"
#include "Player.h"

StatManager* StatManager::Inst;

StatManager::StatManager()
{
	Inst = this;
}

StatManager::~StatManager()
{

}

void StatManager::ChangeHp(std::shared_ptr<StatDataPlayer> _Stat, float _Damage)
{
	_Stat->CurHp -= _Damage;

	float MaxHp = _Stat->MaxHp;
	float GaugeSizeX = UI_Status::Inst->HpGaugeSize.X;
	float ConvertedHp = -_Damage * (GaugeSizeX / MaxHp);
	UI_Status::Inst->ChangeHpGauge(ConvertedHp);
}

void StatManager::ChangeHp(std::shared_ptr<StatDataMonster> _Stat, float _Damage)
{
	_Stat->CurHp -= _Damage;
}

void StatManager::ChangeExp(float _Exp)
{
	//std::shared_ptr<StatDataPlayer> stat = Player::MainPlayer->GetStat()->GetDynamic_Cast_This<StatDataPlayer>();
	//stat->CurExp += _Exp;

	//float MaxExp = stat->MaxExp;
	//float GaugeSizeX = ContentsCore::GetStartWindowSize().X;
	//float ConvertedExp = _Exp * (GaugeSizeX / MaxExp);

	//UI_Status::Inst->ChangeExpGauge(ConvertedExp);

	//if (stat->CurExp > stat->MaxExp)
	//{
	//	stat->CurExp = 0.0f;
	//	stat->CurLevel += 1;
	//	UI_Status::Inst->LevelUp(stat->CurLevel);
	//}
	//
}





