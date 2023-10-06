#include "PreCompile.h"
#include "KCityMap.h"
#include "Portal.h"
#include "Monster.h"

KCityMap::KCityMap()
{
	
}

KCityMap::~KCityMap()
{

}

void KCityMap::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("kerningcity", 0);
		Renderer0->SetRenderOrder(-10);

		Renderer0->Transform.SetLocalScale({ 1.3, 1.3 });
		Renderer0->Transform.AddLocalPosition({ 0,0,100 });
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer1->SetSprite("kerningcity", 1);
		Renderer1->SetRenderOrder(-9);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(2);
		DebugRenderer->SetSprite("kerningcity", 2);
		DebugRenderer->SetRenderOrder(-8);
	    //Renderer2->Off();
	}

	MapScale = Renderer0->GetSprite()->GetSpriteData(1).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void KCityMap::Update(float _Delta)
{

}


