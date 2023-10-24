#include "PreCompile.h"
#include "KerningCity.h"
#include "Map0.h"
#include "Monster.h"
#include "MonsterSpawner.h"

KerningCity::KerningCity() 
{
}

KerningCity::~KerningCity() 
{
}

void KerningCity::Start()
{
	MapleLevel::Start();
	{
		CurMap = CreateActor<Map0>(ActorOrder::Map);
		SetName(std::string("KerningCity"));
		CreatePortal("HuntRegion", { 310, -1033 });
	}
	{
		//CreateActor<MonsterSpawner>(ActorOrder::Manager)->Setting("Octopus", 10.0f, 10);
	}
}

void KerningCity::Update(float _Delta)
{
	MapleLevel::Update(_Delta);

	
}

void KerningCity::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
	
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	MapleLevel::LevelEnd(_NextLevel);
}
