#include "PreCompile.h"
#include "KerningCity.h"
#include "Map0.h"
#include "Monster.h"

KerningCity::KerningCity() 
{
}

KerningCity::~KerningCity() 
{
}

void KerningCity::Start()
{
	GameEngineGUI::CreateGUIWindow<TestGUIWindow>("Test");

	MapleLevel::Start();
	{
		CurMap = CreateActor<Map0>(ActorOrder::Map);
		CreatePortal("HuntRegion", { 310, -910 });
	}
	{
		CreateActor<Monster>(ActorOrder::Monster);
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
	
}
