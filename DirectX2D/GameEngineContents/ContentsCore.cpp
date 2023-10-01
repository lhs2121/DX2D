#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KCityLevel.h"
#include "TitleLevel.h"
#include "HuntLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<KCityLevel>("KCityLevel");
	GameEngineCore::CreateLevel<HuntLevel>("HuntLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("KCityLevel");

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}