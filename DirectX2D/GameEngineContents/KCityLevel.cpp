#include "PreCompile.h"
#include "KCityLevel.h"
#include "Player.h"
#include "KCityMap.h"
#include "Portal.h"
#include "Monster.h"

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
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);
		CreateActor<KCityMap>(ContentsObjectType::Map);
		CreateActor<Portal>(ContentsObjectType::MapObject);
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
}

void KCityLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void KCityLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}