#include "PreCompile.h"
#include "TownLevel.h"
#include "Map0.h"

TownLevel::TownLevel() 
{
}

TownLevel::~TownLevel() 
{
}

void TownLevel::Start()
{
	MapleLevel::Start();
	{
		CurMap = CreateActor<Map0>(ActorOrder::Map);
		SetName(std::string("TownLevel"));
		CreatePortal("HuntLevel", { 3784, -1212 });
	}
}

void TownLevel::Update(float _Delta)
{
	MapleLevel::Update(_Delta);
}

void TownLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
	
}

void TownLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	MapleLevel::LevelEnd(_NextLevel);
}
