#include "PreCompile.h"
#include "MapleLevel.h"
#include "Player.h"
#include "Portal.h"
#include "UI_Status.h"
#include "MapleMap.h"
#include "SkillManager.h"
#include "FadeScreen.h"
#include "UI_Inventory.h"
#include "MouseActor.h"
#include "StatManager.h"
#include "UI_Buff.h"

MapleLevel::MapleLevel()
{
}

MapleLevel::~MapleLevel()
{
}

std::shared_ptr<Portal> MapleLevel::CreatePortal(std::string _NextLevel, float4 _Pos)
{
    std::shared_ptr<Portal> NewPortal = CreateActor<Portal>(ActorOrder::Portal);
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
}

void MapleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<MouseActor>(ActorOrder::UI);

	{
		CurPlayer = CreateActor<Player>(ActorOrder::Player);
		CurSkillManager = CreateActor<SkillManager>(ActorOrder::Manager);
		CurFadeScreen = CreateActor<FadeScreen>(ActorOrder::FadeScreen);
		CurStatus = CreateActor<UI_Status>(ActorOrder::UI);
		CurInventory = CreateActor<UI_Inventory>(ActorOrder::UI_Inventory);
		UI_Buff::Inst = CreateActor<UI_Buff>(ActorOrder::UI_Inventory);
	}

	{
		Player::MainPlayer = CurPlayer.get();
		SkillManager::Inst = CurSkillManager.get();
		MapleMap::CurMap = CurMap.get();
		UI_Inventory::Inst = CurInventory.get();
		StatManager::Inst->AddPlayerStatus(CurStatus);
	}

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
	if (InputIsDown('I'))
	{
		if (CurInventory->IsUpdate())
		{
			CurInventory->Off();
		}
		else
		{
			CurInventory->On();
		}
	}
}


