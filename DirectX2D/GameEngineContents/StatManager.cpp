#include "PreCompile.h"
#include "StatManager.h"
#include "Player.h"
#include "PlayerStat.h"
#include "ExpBar.h"
#include "StatusBar.h"

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

void StatManager::ChangeHp(float _HpValue)
{
	PlayerStat::Inst->CurHp += _HpValue;

	float MaxHp = PlayerStat::Inst->MaxHp;
	float GaugeSizeX = StatusBar::Inst->HpGaugeSizeX;
	float ConvertedHp = _HpValue * (GaugeSizeX / MaxHp); 
	StatusBar::Inst->ChangeHpGauge(ConvertedHp);

	if (PlayerStat::Inst->CurHp <= 0)
	{
		Player::MainPlayer->Death();
	}
	if (PlayerStat::Inst->CurHp >= PlayerStat::Inst->MaxHp)
	{
		PlayerStat::Inst->CurHp = PlayerStat::Inst->MaxHp;
	}
}

void StatManager::ChangeMp(float _MpValue)
{
	PlayerStat::Inst->CurMp += _MpValue;

	float MaxMp = PlayerStat::Inst->MaxMp;
	float GaugeSizeX = StatusBar::Inst->MpGaugeSizeX;
	float ConvertedMp = _MpValue * (GaugeSizeX / MaxMp);
	StatusBar::Inst->ChangeHpGauge(ConvertedMp);
}

void StatManager::ChangeExp(float _ExpValue)
{
	PlayerStat::Inst->CurExp += _ExpValue;

	float MaxExp = PlayerStat::Inst->MaxExp;
	float GaugeSizeX = ContentsCore::GetStartWindowSize().X;
	float ConvertedExp = _ExpValue * (GaugeSizeX / MaxExp);

	ExpBar::Inst->ChangeExpGauge(ConvertedExp);

	if (PlayerStat::Inst->CurExp >= PlayerStat::Inst->MaxExp)
	{
		PlayerStat::Inst->CurExp = 0;
		PlayerStat::Inst->MaxExp += 100;
		PlayerStat::Inst->CurLevel += 1;
	}
}
