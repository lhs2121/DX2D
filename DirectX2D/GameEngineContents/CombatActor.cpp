#include "PreCompile.h"
#include "CombatActor.h"
#include "DamageEffectController.h"

CombatActor::CombatActor()
{
}
CombatActor::~CombatActor()
{
}
void CombatActor::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 50,50 });
		Col->Transform.SetLocalPosition({ 0,50 });
	}
	HitDmgEffController = GetLevel()->CreateActor<DamageEffectController>();
}

void CombatActor::Update(float _Delta)
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			hp -= 30.0f;
			Col2->GetParentObject()->Off();
			std::random_device rnd;
			GameEngineRandom rd = GameEngineRandom();
			rd.SetSeed(rnd());
			HitDmgEffController->StartEffect(Transform.GetWorldPosition() + float4(-70.0f, 70.0f), rd.RandomFloat(999999, 9999999));
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(EnemyColOrder, Event);

	if (hp <= 0)
	{
		Death();
	}
}

