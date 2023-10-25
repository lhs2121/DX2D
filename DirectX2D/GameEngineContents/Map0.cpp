#include "PreCompile.h"
#include "Map0.h"
#include "Portal.h"
#include "Monster.h"

Map0::Map0()
{

}

Map0::~Map0()
{

}

void Map0::Start()
{
	{
		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer0->SetSprite("Map_Town_BG.png");
		Renderer0->SetRenderOrder(RenderOrder::MapBackground);
	}

	{
		Renderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer1->SetSprite("Map_Town_Tile.png");
		Renderer1->SetRenderOrder(RenderOrder::MapTile);
	}

	{
		DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer->SetSprite("Map_Town_Ground.png");
		DebugRenderer->SetRenderOrder(RenderOrder::Debug);
		DebugRenderer->Off();
	}

	MapScale = DebugRenderer->GetSprite()->GetSpriteData(0).GetScale();
	Transform.SetLocalPosition({ MapScale.hX(), -MapScale.hY(), 0.0f });
}

void Map0::Update(float _Delta)
{
	Renderer0->Transform.SetWorldPosition({ DebugRenderer->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y});
}


