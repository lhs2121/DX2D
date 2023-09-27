#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 100,100 });
	}

	{
		CollisionRenderer = CreateComponent<GameEngineSpriteRenderer>(1);
		CollisionRenderer->SetRenderOrder(32);
		CollisionRenderer->SetSprite("etc", 1);
		CollisionRenderer->SetImageScale({ 100,100 });
		CollisionRenderer->Off();
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(2);
		Renderer->SetSprite("m0stand");
		Renderer->SetRenderOrder(40);
		Renderer->SetPivotType(PivotType::Bottom);
	}

	Col->Transform.SetLocalPosition(Renderer->Transform.GetLocalPosition());
	Transform.SetLocalPosition({ 700, -300, 0.0f });
}


void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
}
