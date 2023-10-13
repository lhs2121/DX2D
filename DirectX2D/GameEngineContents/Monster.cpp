#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 50,50 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("m0stand");
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
	}

	Col->Transform.SetLocalPosition({ 0,50 });
	Transform.SetLocalPosition({ 700, -300, 0.0f });

}


void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);	
}
