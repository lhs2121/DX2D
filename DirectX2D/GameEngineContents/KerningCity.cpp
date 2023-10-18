#include "PreCompile.h"
#include "KerningCity.h"
#include "Map0.h"
#include "Portal.h"
#include "PlayerStat.h"
#include "Monster.h"
#include "DamageEffctor.h"

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
		CreatePortal("HuntRegion", { 310, -910 });
	}
	{
		CreateActor<Monster>(ActorOrder::Monster);
		CurDamageEffctor = CreateActor<DamageEffctor>(ActorOrder::Manager);
	}
}

void KerningCity::Update(float _Delta)
{
	MapleLevel::Update(_Delta);

	if (InputIsDown('N'))
	{
		std::random_device rnd;
		GameEngineRandom rd = GameEngineRandom();
		rd.SetSeed(rnd());
		CurDamageEffctor->StartEffect({ 500, -1100 }, rd.RandomFloat(9999999, 99999999));
	}
}

void KerningCity::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleLevel::LevelStart(_PrevLevel);
	
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}
