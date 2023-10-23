#include "PreCompile.h"
#include "TitleLevel.h"
#include "StatData.h"
#include "StatManager.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Assets");
		Dir.MoveChild("Assets");

		std::vector<GameEngineDirectory> DirGroup = Dir.GetAllDirectory();

		for (int i = 0; i < DirGroup.size(); i++)
		{
            GameEngineSprite::CreateFolder(DirGroup[i].GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("HpGauge.png");
	GameEngineSprite::CreateSingle("MpGauge.png");
	GameEngineSprite::CreateSingle("LvText.png");
	GameEngineSprite::CreateSingle("StatusBG.png");
	GameEngineSprite::CreateSingle("StatusCover.png");
	GameEngineSprite::CreateSingle("QuickSlotBG.png");
	GameEngineSprite::CreateSingle("QuickSlotCover.png");
	GameEngineSprite::CreateSingle("QuickSlotExpandButton.png");

	GameEngineSprite::CreateSingle("1366ExpCover.png");
	GameEngineSprite::CreateSingle("1366ExpCover2.png");
	GameEngineSprite::CreateSingle("1366ExpCover3.png");
	GameEngineSprite::CreateSingle("1366ExpGauge.png");
	GameEngineSprite::CreateSingle("1366ExpEffect.png");

	GameEngineSprite::CreateSingle("1920ExpCover.png");
	GameEngineSprite::CreateSingle("1920ExpCover2.png");
	GameEngineSprite::CreateSingle("1920ExpCover3.png");
	GameEngineSprite::CreateSingle("1920ExpGauge.png");
	GameEngineSprite::CreateSingle("1920ExpEffect.png");

	GameEngineSprite::CreateSingle("MainBossUI.png");

	{
		CreateActor<StatManager>(ActorOrder::Manager);
	}
	
}

void TitleLevel::Update(float _Delta)
{

}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

