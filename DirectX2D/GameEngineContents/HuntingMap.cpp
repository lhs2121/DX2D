#include "PreCompile.h"
#include "HuntingMap.h"
#include "Portal.h"
#include "Monster.h"
#include "Player.h"

HuntingMap::HuntingMap()
{

}

HuntingMap::~HuntingMap()
{

}

void HuntingMap::Start()
{
	{
		CreatePortal("KCityLevel", { 310, -1210 });
	}

	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("huntzone", 1);
		Renderer0->SetRenderOrder(-10);

		Renderer0->Transform.SetLocalScale({ 1.3, 1.3 });
		Renderer0->Transform.AddLocalPosition({ 0,0,100 });
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

void HuntingMap::Update(float _Delta)
{
	
}
