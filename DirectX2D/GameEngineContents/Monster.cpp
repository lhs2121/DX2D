#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "DamageEffctor.h"
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

	{
		MyDamageEffctor = GetLevel()->CreateActor<DamageEffctor>();
	}

	Col->Transform.SetLocalPosition({ 0,50 });
	Transform.SetLocalPosition({ 700, -300, 0.0f });

}


void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);	
	ColCheck();

}

void Monster::ColCheck()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			hp -= 5.0f;

			std::random_device rnd;
			GameEngineRandom rd = GameEngineRandom();
			rd.SetSeed(rnd());
			MyDamageEffctor->StartEffect(Transform.GetWorldPosition() + float4(-70.0f,70.0f), rd.RandomFloat(9999999, 99999999));
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(CollisionOrder::PlayerWeapon, Event);

	if (hp <= 0)
	{
		Death();
	}
}
