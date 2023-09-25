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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetSprite("m0stand");
	//Renderer->SetSamplerState(SamplerOption::POINT);
	Renderer->SetRenderOrder(40);
	Transform.SetLocalPosition({ 700, -300, 0.0f });
	Renderer->SetPivotType(PivotType::Bottom);

	Col = CreateComponent<GameEngineCollision>(1);
	Col->SetCollisionType(ColType::AABBBOX2D);
	Col->Transform.SetLocalScale({ 100,100 });
}


void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
}
