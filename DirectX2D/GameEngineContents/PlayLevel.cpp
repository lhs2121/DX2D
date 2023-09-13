#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"
#include "BackGround.h"

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

		std::vector<GameEngineDirectory> DirGroup = Dir.GetAllDirectory();

		for (int i = 0; i < DirGroup.size(); i++)
		{
			GameEngineSprite::CreateFolder(DirGroup[i].GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");
		Dir.MoveChild("Maps");
		Dir.MoveChild("kerningcity");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);
		CurMap = CreateActor<BackGround>(ContentsObjectType::BackGround);

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
