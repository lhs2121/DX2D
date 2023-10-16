#include "PreCompile.h"
#include "PlayerStat.h"

PlayerStat* PlayerStat::Inst = nullptr;

PlayerStat::PlayerStat()
{
	Inst = this;
}

PlayerStat::~PlayerStat()
{
}

void PlayerStat::Start()
{
}

void PlayerStat::Update(float _Delta)
{
}

void PlayerStat::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayerStat::LevelEnd(GameEngineLevel* _NextLevel)
{

}


