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
		CreatePortal("KerningCity", { 1010, -1100 });
	}
	{
		CreateActor<Monster>(ActorOrder::Monster);
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

}
