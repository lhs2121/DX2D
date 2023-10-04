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
	Col->CollisionEvent(ContentsCollisionType::Monster, Event);
}

void ProJectile::StartCoolTime(float _Delta)
{
	CoolTime -= _Delta;

	if (CoolTime <= 0)
	{
		CoolTime = 2.0f;

		Off();
	}
}

void ProJectile::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerWeapon);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 30,30 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(2);
		Renderer->CreateAnimation("Sureken", "Sureken", 0.1f, 0, 1, true);
		Renderer->SetSprite("Sureken");
		Renderer->ChangeAnimation("Sureken");
		Renderer->SetRenderOrder(50);
	}


}

void ProJectile::Update(float _Delta)
{
	Move(_Delta);
	ColCheck();
	StartCoolTime(_Delta);
}
