#include "PreCompile.h"
#include "ProJectile.h"
#include "Player.h"

ProJectile::ProJectile()
{
}

ProJectile::~ProJectile()
{
}

void ProJectile::Move(float _Delta)
{
	float4 Force = { Dir * Speed * _Delta, 0 };
	Transform.AddWorldPosition(Force);
}

void ProJectile::ColCheck()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Off();
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(CollisionOrder::Monster, Event);
}

void ProJectile::StartCoolTime(float _Delta)
{
	CoolTime -= _Delta;

	if (CoolTime <= 0)
	{
		Off();
	}
}

void ProJectile::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerWeapon);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 20,20 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer->CreateAnimation("Sureken", "Sureken", 0.1f, 0, 1, true);
		Renderer->SetSprite("Sureken");
		Renderer->ChangeAnimation("Sureken");
		Renderer->SetImageScale({ 20,20 });
		Renderer->SetRenderOrder(RenderOrder::Projectile);
	}

	Off();
}

void ProJectile::Update(float _Delta)
{
	Move(_Delta);
	ColCheck();
	StartCoolTime(_Delta);
}
