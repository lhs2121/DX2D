#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineMaterial.h>
#include "KerningCity.h"
#include "TitleLevel.h"
#include "HuntRegion.h"
#include "BossLevel.h"
#include "ContentsControlWindow.h"

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
	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<KerningCity>("KerningCity");
	GameEngineCore::CreateLevel<HuntRegion>("HuntRegion");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::ChangeLevel("KerningCity");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}