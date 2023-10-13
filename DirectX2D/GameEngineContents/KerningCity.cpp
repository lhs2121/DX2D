#include "PreCompile.h"
#include "KerningCity.h"
#include "Player.h"
#include "KerningCityBG.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"
#include "LuckySeven.h"
#include "EffectManager.h"

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
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");

		std::vector<GameEngineDirectory> DirGroup = Dir.GetAllDirectory();
		
		for (int i = 0; i < DirGroup.size(); i++)
		{
			std::vector<GameEngineDirectory> DirGroup2 = DirGroup[i].GetAllDirectory();

			for (int j = 0; j < DirGroup2.size(); j++)
			{
				GameEngineSprite::CreateFolder(DirGroup2[j].GetStringPath());
			}
		}
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -600.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		Map = CreateActor<KerningCityBG>(ActorOrder::Map);
		luckySeven = CreateActor<LuckySeven>(ActorOrder::Skill);
		player = CreateActor<Player>(ActorOrder::Player);
		CreatePortal("HuntRegion", { 310, -910 });
		CreateActor<Monster>(ActorOrder::Monster);
		CreateActor<EffectManager>(ActorOrder::Effect)->Transform.SetWorldPosition(player->Transform.GetWorldPosition());
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
		GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -600.0f });
	}
	if (InputIsDown(VK_END))
	{
		GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -150.0f });
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
	LuckySeven::Inst = luckySeven.get();
	MapleMap::SetCurMap(Map);
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}
