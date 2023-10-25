#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>

#include "TitleLevel.h"
#include "TownLevel.h"
#include "HuntLevel.h"
#include "BossLevel.h"

#include "MapleStoryGUI.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineLevel::OffDebug();
    GameEngineRenderTarget::IsDepth = false;
	GameEngineGUI::CreateGUIWindow<MapleStoryGUI>("MapleStoryGUI");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TownLevel>("TownLevel");
	GameEngineCore::CreateLevel<HuntLevel>("HuntLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::ChangeLevel("TownLevel");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}