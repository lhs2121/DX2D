#include "PreCompile.h"
#include "HuntRegion.h"
#include "Player.h"
#include "Map1.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"
#include "BulletShooter.h"

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
		Map = CreateActor<Map1>(ActorOrder::Map);
		CreatePortal("KerningCity", { 1010, -1100 });
	}
	{
		bulletShooter = CreateActor<BulletShooter>(ActorOrder::Skill);
		player = CreateActor<Player>(ActorOrder::Player);
		CreateActor<Monster>(ActorOrder::Monster);
	}
}

void HuntRegion::Update(float _Delta)
{
	if (InputIsPress('Q'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,500 * _Delta });
	}
	if (InputIsPress('E'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,-500 * _Delta });
	}
	if (InputIsDown('C'))
	{
		IsDebug = !IsDebug;
	}
	if (InputIsDown('P'))
	{
		MapleMap::CurMap->SwitchDebugRender();
	}
}

void HuntRegion::LevelStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer = player.get();
	BulletShooter::Inst = bulletShooter.get();
	MapleMap::SetCurMap(Map);
}

void HuntRegion::LevelEnd(GameEngineLevel* _NextLevel)
{

}
