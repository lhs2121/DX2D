#include "PreCompile.h"
#include "HuntRegion.h"
#include "Map1.h"
#include "Monster.h"
#include "ExpBar.h"
#include "StatData.h"
HuntRegion::HuntRegion()
{
}

HuntRegion::~HuntRegion()
{
}

void HuntRegion::Start()
{
	MapleLevel::Start();
	{
		CurMap = CreateActor<Map1>(ActorOrder::Map);
		SetName(std::string("HuntRegion"));
		CreatePortal("KerningCity", { 74, -1253 });
	}
	{

	}
}

void HuntRegion::Update(float _Delta)
{
	MapleLevel::Update(_Delta);
}

void HuntRegion::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
}

void HuntRegion::LevelEnd(GameEngineLevel* _NextLevel)
{
	MapleLevel::LevelEnd(_NextLevel);
}
