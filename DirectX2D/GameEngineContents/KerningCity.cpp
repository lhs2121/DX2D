#include "PreCompile.h"
#include "KerningCity.h"
#include "Player.h"
#include "Monster.h"
#include "Map0.h"
#include "Portal.h"

KerningCity::KerningCity() 
{
}

KerningCity::~KerningCity() 
{
}

void KerningCity::Start()
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");
		Dir.MoveChild("Character");

		GameEngineDirectory Dir2;
		Dir2 = Dir;
		Dir2.MoveChild("etc");
		GameEngineSprite::CreateFolder(Dir2.GetStringPath());

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");
		Dir.MoveChild("Maps");
		Dir.MoveChild("portal");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);
		CurMap = CreateActor<Map0>(ContentsObjectType::Map0);
		CreateActor<Portal>(ContentsObjectType::MapObject);
	}
}

void KerningCity::Update(float _Delta)
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

void KerningCity::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void KerningCity::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
