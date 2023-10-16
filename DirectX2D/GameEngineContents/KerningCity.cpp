#include "PreCompile.h"
#include "KerningCity.h"
#include "Player.h"
#include "Map0.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"
#include "BulletShooter.h"
#include "EffectManager.h"
#include "StatusBar.h"

KerningCity::KerningCity() 
{
}

KerningCity::~KerningCity() 
{
}

void KerningCity::Start()
{
	MapleLevel::Start();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -600.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		Map = CreateActor<Map0>(ActorOrder::Map);
		bulletShooter = CreateActor<BulletShooter>(ActorOrder::Skill);
		player = CreateActor<Player>(ActorOrder::Player);
		CreatePortal("HuntRegion", { 310, -910 });
		CreateActor<Monster>(ActorOrder::Monster);
		CreateActor<EffectManager>(ActorOrder::Effect)->Transform.SetWorldPosition(player->Transform.GetWorldPosition());
		CreateActor<StatusBar>(ActorOrder::UI);
	}
}

void KerningCity::Update(float _Delta)
{
	if (InputIsPress(VK_PRIOR))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,500 * _Delta });
	}
	if (InputIsPress(VK_NEXT))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,-500 * _Delta });
	}
	if (InputIsDown(VK_HOME))
	{
		GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	}
	if (InputIsDown(VK_END))
	{
		GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
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

void KerningCity::LevelStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer = player.get();
	BulletShooter::Inst = bulletShooter.get();
	MapleMap::SetCurMap(Map);

	IsDebug = false;
	MapleMap::CurMap->SwitchDebugRender();
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}
