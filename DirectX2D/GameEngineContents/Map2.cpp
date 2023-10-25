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
		Renderer0->SetSprite("Map_Boss_BG.png");
		Renderer0->SetRenderOrder(RenderOrder::MapBackground);
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer1->SetSprite("Map_Boss_Tile.png");
		Renderer1->SetRenderOrder(2);
	}

	{
		Renderer2 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer2->SetSprite("Map_Boss_Object.png");
		Renderer2->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer->SetSprite("Map_Boss_Ground.png");
		DebugRenderer->SetRenderOrder(RenderOrder::Debug);
		DebugRenderer->Off();
	}

	MapScale = DebugRenderer->GetSprite()->GetSpriteData(0).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void Map2::Update(float _Delta)
{
	Renderer0->Transform.SetWorldPosition({ DebugRenderer->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y });
}
