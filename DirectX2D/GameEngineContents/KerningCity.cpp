#include "PreCompile.h"
#include "KerningCity.h"
#include "Map0.h"
#include "Portal.h"
#include "PlayerStat.h"

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
		CreateActor<PlayerStat>(ActorOrder::Manager);
		CurMap = CreateActor<Map0>(ActorOrder::Map);
		CreatePortal("HuntRegion", { 310, -910 });
	}
}

void KerningCity::Update(float _Delta)
{
	MapleLevel::Update(_Delta);

	if (InputIsDown('C'))
	{
		PlayerStat::Inst->curhp -= 10.0f;
	}
}

void KerningCity::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
	
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}
