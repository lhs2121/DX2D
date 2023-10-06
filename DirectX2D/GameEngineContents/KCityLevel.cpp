#include "PreCompile.h"
#include "KCityLevel.h"
#include "Player.h"
#include "KCityMap.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"

KCityLevel::KCityLevel() 
{
}

KCityLevel::~KCityLevel() 
{
}

void KCityLevel::Start()
{
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

	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		CreateActor<Player>(ContentsObjectType::Player);
		Map = CreateActor<KCityMap>(ContentsObjectType::Map);
	}

	{
		CreatePortal("HuntLevel", { 310, -1210 });
	}

	{
		CreateActor<Monster>(ContentsObjectType::Monster);
	}
}

void KCityLevel::Update(float _Delta)
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

void KCityLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleMap::SetCurMap(Map);
}

void KCityLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}
