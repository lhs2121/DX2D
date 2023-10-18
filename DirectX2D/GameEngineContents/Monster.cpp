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
	CombatActor::Start();
	SetEnemyOrder(CollisionOrder::PlayerWeapon);
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("m0stand");
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
	}

	Transform.SetLocalPosition({ 700, -300, 0.0f });
}


void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);	
	CombatActor::Update(_Delta);
}

