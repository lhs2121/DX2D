#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KerningCity.h"
#include "TitleLevel.h"
#include "HuntRegion.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineRenderTarget::IsDepth = false;
	GameEngineCore::CreateLevel<KerningCity>("KerningCity");
	GameEngineCore::CreateLevel<HuntRegion>("HuntRegion");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("KerningCity");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}