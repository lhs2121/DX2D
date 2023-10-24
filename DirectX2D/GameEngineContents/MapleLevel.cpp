#include "PreCompile.h"
#include "MapleLevel.h"
#include "Player.h"
#include "Portal.h"
#include "StatusBar.h"
#include "BulletShooter.h"
#include "ExpBar.h"
#include "MapleMap.h"
#include "SkillEffctor.h"
#include "FadeScreen.h"

MapleLevel::MapleLevel()
{
}

MapleLevel::~MapleLevel()
{
}

std::shared_ptr<Portal> MapleLevel::CreatePortal(std::string _NextLevel, float4 _Pos)
{
    std::shared_ptr<Portal> NewPortal = CreateActor<Portal>(ActorOrder::MapObject);
    NewPortal->SetNextMap(_NextLevel);
    NewPortal->Transform.SetWorldPosition(_Pos);
    PortalGroup.insert(std::make_pair(_NextLevel, NewPortal));
    return NewPortal;
}

void MapleLevel::Start()
{
    GameEngineInput::AddInputObject(this);

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -600.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		CurPlayer = CreateActor<Player>(ActorOrder::Player);
		CurShooter = CreateActor<BulletShooter>(ActorOrder::Manager);
		CurSkillEffctor = CreateActor<SkillEffctor>(ActorOrder::Manager);
		CurStatusBar = CreateActor<StatusBar>(ActorOrder::UI);
		CurExpBar = CreateActor<ExpBar>(ActorOrder::UI);
		CurFadeScreen = CreateActor<FadeScreen>(ActorOrder::FadeScreen);
	}
}

void MapleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer = CurPlayer.get();
	BulletShooter::Inst = CurShooter.get();
	SkillEffctor::Inst = CurSkillEffctor.get();
	StatusBar::Inst = CurStatusBar.get();
	ExpBar::Inst = CurExpBar.get();
	MapleMap::CurMap = CurMap.get();
	CurFadeScreen->SettingAndStart(FadeType::FADEOUT);
}

void MapleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void MapleLevel::Update(float _Delta)
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


