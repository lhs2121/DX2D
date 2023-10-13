#include "PreCompile.h"
#include "KerningCityBG.h"
#include "Portal.h"
#include "Monster.h"

KerningCityBG::KerningCityBG()
{

}

KerningCityBG::~KerningCityBG()
{

}

void KerningCityBG::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("kerningcity", 0);
		Renderer0->SetRenderOrder(RenderOrder::MapBackground);
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer1->SetSprite("kerningcity", 1);
		Renderer1->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer->SetSprite("kerningcity", 2);
		DebugRenderer->SetRenderOrder(RenderOrder::Debug);
		//Renderer2->Off();
	}

	MapScale = Renderer0->GetSprite()->GetSpriteData(1).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void KerningCityBG::Update(float _Delta)
{

}


