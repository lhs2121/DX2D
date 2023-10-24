#include "PreCompile.h"
#include "Map2.h"

Map2::Map2()
{

}

Map2::~Map2()
{

}

void Map2::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("bossmap", 0);
		Renderer0->SetRenderOrder(RenderOrder::MapBackground);
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer1->SetSprite("bossmap", 1);
		Renderer1->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		Renderer2 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer2->SetSprite("bossmap", 2);
		Renderer2->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer->SetSprite("bossmap", 3);
		DebugRenderer->SetRenderOrder(RenderOrder::Debug);
		//Renderer2->Off(); 
	}

	MapScale = Renderer0->GetSprite()->GetSpriteData(0).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void Map2::Update(float _Delta)
{

}
