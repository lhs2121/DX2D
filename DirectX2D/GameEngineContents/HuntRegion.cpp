#include "PreCompile.h"
#include "HuntRegion.h"
#include "Player.h"
#include "HuntRegionBG.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"
#include "LuckySeven.h"

HuntRegion::HuntRegion()
{
}

HuntRegion::~HuntRegion()
{
}

void HuntRegion::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		Map = CreateActor<HuntRegionBG>(ActorOrder::Map);
		CreatePortal("KerningCity", { 1010, -1100 });
	}
	{
		luckySeven = CreateActor<LuckySeven>(ActorOrder::Skill);
		player = CreateActor<Player>(ActorOrder::Player);
		CreateActor<Monster>(ActorOrder::Monster);
	}
}

void HuntRegion::Update(float _Delta)
{
	if (GameEngineInput::IsPress('Q'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,500 * _Delta });
	}
	if (GameEngineInput::IsPress('E'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,-500 * _Delta });
	}
	if (GameEngineInput::IsDown('C'))
	{
		IsDebug = !IsDebug;
	}
	if (GameEngineInput::IsDown('P'))
	{
		MapleMap::CurMap->SwitchDebugRender();
	}
}

void HuntRegion::LevelStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer = player.get();
	LuckySeven::Inst = luckySeven.get();
	MapleMap::SetCurMap(Map);
}

void HuntRegion::LevelEnd(GameEngineLevel* _NextLevel)
{

}
