#include "PreCompile.h"
#include "TitleLevel.h"
#include "PlayerStat.h"
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
			if (DirGroup[i].GetAllFile().size() == 0)
			{
				continue;
			}
            GameEngineSprite::CreateFolder(DirGroup[i].GetStringPath());
		}
	}
	GameEngineSprite::CreateSingle("HpGauge.png");
	GameEngineSprite::CreateSingle("MpGauge.png");
	GameEngineSprite::CreateSingle("LvText.png");
	GameEngineSprite::CreateSingle("StatusCover.png");
	GameEngineSprite::CreateSingle("QuickSlotBG.png");
	GameEngineSprite::CreateSingle("QuickSlotCover.png");
	GameEngineSprite::CreateSingle("QuickSlotExpandButton.png");
	GameEngineSprite::CreateSingle("ExpBG.png");
	GameEngineSprite::CreateSingle("ExpCover.png");
	GameEngineSprite::CreateSingle("ExpCover2.png");
	GameEngineSprite::CreateSingle("ExpCover3.png");
	GameEngineSprite::CreateSingle("ExpGauge.png");
	GameEngineSprite::CreateSingle("ExpEffect.png");
	GameEngineSprite::CreateSingle("MainBossUI.png");

	{
		CreateActor<PlayerStat>(ActorOrder::Manager);
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

