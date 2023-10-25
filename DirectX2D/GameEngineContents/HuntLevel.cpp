#include "PreCompile.h"
#include "HuntLevel.h"
#include "Map1.h"
#include "MonsterSpawner.h"
HuntLevel::HuntLevel()
{
}

HuntLevel::~HuntLevel()
{
}

void HuntLevel::Start()
{
	MapleLevel::Start();
	{
		CurMap = CreateActor<Map1>(ActorOrder::Map);
		SetName(std::string("HuntLevel"));
		CreatePortal("TownLevel", { 178, -749 });
	}
	{
		std::vector<float4> SpawnPoint = { {1233,-749},{1389,-749},{1241,-928},{883,-928},{1003,-928},{1297,-928},
			{1750,-868},{2150,-868},{2553,-868},{2365,-629},{177,-988},{302,-988} };

		CreateActor<MonsterSpawner>(ActorOrder::Manager)->Setting("Octopus", 10.0f, 2, SpawnPoint);
	}
}

void HuntLevel::Update(float _Delta)
{
	MapleLevel::Update(_Delta);
}

void HuntLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
}

void HuntLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	MapleLevel::LevelEnd(_NextLevel);
}
