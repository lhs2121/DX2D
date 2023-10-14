#include "PreCompile.h"
#include "Map1.h"
#include "Portal.h"
#include "Monster.h"
#include "Player.h"

Map1::Map1()
{

}

Map1::~Map1()
{

}

void Map1::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("huntzone", 1);
		Renderer0->SetRenderOrder(RenderOrder::MapBackground);
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer1->SetSprite("huntzone", 0);
		Renderer1->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer->SetSprite("huntzone", 2);
		DebugRenderer->SetRenderOrder(RenderOrder::Debug);
		//Renderer2->Off(); 
	}

	MapScale = Renderer0->GetSprite()->GetSpriteData(0).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void Map1::Update(float _Delta)
{

}
