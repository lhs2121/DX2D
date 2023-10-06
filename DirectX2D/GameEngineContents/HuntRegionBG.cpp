#include "PreCompile.h"
#include "HuntRegionBG.h"
#include "Portal.h"
#include "Monster.h"
#include "Player.h"

HuntRegionBG::HuntRegionBG()
{

}

HuntRegionBG::~HuntRegionBG()
{

}

void HuntRegionBG::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("huntzone", 1);
		Renderer0->SetRenderOrder(-10);

		Renderer0->Transform.SetLocalScale({ 1.3f, 1.3f });
		Renderer0->Transform.AddLocalPosition({ 0.0f,0.0f,100.0f });
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer1->SetSprite("huntzone", 0);
		Renderer1->SetRenderOrder(-9);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(2);
		DebugRenderer->SetSprite("huntzone", 2);
		DebugRenderer->SetRenderOrder(-8);
		//Renderer2->Off(); 
	}

	MapScale = Renderer0->GetSprite()->GetSpriteData(0).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void HuntRegionBG::Update(float _Delta)
{

}
