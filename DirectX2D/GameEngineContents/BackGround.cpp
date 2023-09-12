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

void BackGround::Start()
{
	Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer0->SetSamplerState(SamplerOption::POINT);
	Renderer0->SetSprite("kerningcity", 0);

	Renderer1 = CreateComponent<GameEngineSpriteRenderer>(1);
	Renderer1->SetSamplerState(SamplerOption::POINT);
	Renderer1->SetSprite("kerningcity", 1);

	Renderer0->Transform.AddLocalPosition({ 0,0,200 });
	Renderer0->AddImageScale(1000);


	float4 scale = Renderer0->GetSprite()->GetSpriteData(1).GetScale().Half();



	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ scale.X, -scale.Y, 0.0f });

	GetLevel()->GetCamera(0)->Transform.AddLocalPosition({ scale.X - 250, -scale.Y ,-100 });
}

void BackGround::Update(float _Delta)
{
	float speed = 30.0f;
	GetLevel()->GetCamera(0)->Transform.AddLocalPosition({ speed * _Delta, 0, 0 });
}