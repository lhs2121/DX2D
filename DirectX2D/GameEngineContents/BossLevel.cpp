#include "PreCompile.h"
#include "BossLevel.h"
#include "Map2.h"
#include "Boss_Vellum.h"

BossLevel::BossLevel()
{
}

BossLevel::~BossLevel()
{
}

void BossLevel::Start()
{
	MapleLevel::Start();
	{
		CurMap = CreateActor<Map2>(ActorOrder::Map);
		SetName(std::string("BossLevel"));
		CreatePortal("KerningCity", { 140, -723 });
		CreateActor<Boss_Vellum>(int(ActorOrder::Boss),"Vellum");
	}
	{
		//CreateActor<MonsterSpawner>(ActorOrder::Manager)->Setting("Octopus", 10.0f, 10);
	}
}

void BossLevel::Update(float _Delta)
{
	MapleLevel::Update(_Delta);
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);

}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	MapleLevel::LevelEnd(_NextLevel);
}
