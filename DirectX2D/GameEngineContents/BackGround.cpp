#include "PreCompile.h"
#include "BackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{
}

float4 BackGround::GetMapScale()
{
	return mapScale;
}

void BackGround::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		//Renderer0->SetSamplerState(SamplerOption::LINEAR);
		Renderer0->SetSprite("kerningcity", 0);
		Renderer0->Transform.SetLocalScale({ 1.3, 1.3 });
		Renderer0->Transform.AddLocalPosition({ 0,0,100 });
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(1);
	//	Renderer1->SetSamplerState(SamplerOption::LINEAR);
		Renderer1->SetSprite("kerningcity", 1);
	}

	mapScale = Renderer0->GetSprite()->GetSpriteData(1).GetScale();
	Transform.SetLocalPosition({ mapScale.hX(), -mapScale.hY(), 0.0f });
}

void BackGround::Update(float _Delta)
{

}