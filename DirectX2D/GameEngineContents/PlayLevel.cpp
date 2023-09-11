#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayMap.h"
#include "Monster.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");
		Dir.MoveChild("Character");
		Dir.MoveChild("walk1");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);

	}
}

void PlayLevel::Update(float _Delta)
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
