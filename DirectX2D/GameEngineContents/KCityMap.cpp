#include "PreCompile.h"
#include "KCityMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

KCityMap* KCityMap::MainMap;

KCityMap::KCityMap()
{
	MainMap = this;
}

KCityMap::~KCityMap()
{
}

float4 KCityMap::GetMapScale()
{
	return mapScale;
}

void KCityMap::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSamplerState(SamplerOption::LINEAR);
		Renderer0->SetSprite("kerningcity", 0);
		Renderer0->SetRenderOrder(-5);

		Renderer0->Transform.SetLocalScale({ 1.3, 1.3 });
		Renderer0->Transform.AddLocalPosition({ 0,0,100 });
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer1->SetSamplerState(SamplerOption::LINEAR);
		Renderer1->SetSprite("kerningcity", 1);
		Renderer1->SetRenderOrder(-4);
	}

	{
		Renderer2 = CreateComponent<GameEngineSpriteRenderer>(2);
		Renderer2->SetSamplerState(SamplerOption::POINT);
		Renderer2->SetSprite("kerningcity", 2);
		Renderer2->SetRenderOrder(-3);
		//Renderer2->Off();
	}

	mapScale = Renderer0->GetSprite()->GetSpriteData(1).GetScale();
	Transform.SetLocalPosition({ mapScale.hX(), -mapScale.hY(), 0.0f });
}

GameEngineColor KCityMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("2.png");


	return Tex->GetColor(_Pos, _DefaultColor);
}
void KCityMap::Update(float _Delta)
{

}