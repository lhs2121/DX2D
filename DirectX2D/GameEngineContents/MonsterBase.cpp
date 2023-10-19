#include "PreCompile.h"
#include "MonsterBase.h"
#include "StatData.h"
#include "StatManager.h"
#include "Player.h"
#include "DamageEffectController.h"

MonsterBase::MonsterBase()
{
}

MonsterBase::~MonsterBase()
{
}

void MonsterBase::Start()
{
	{
		HitDmgEffController = GetLevel()->CreateActor<DamageEffectController>();
	}

	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
	}

	{
		MonsterStat = GetLevel()->CreateActor<MonsterStatData>(ActorOrder::MonsterStat);
	}
}


void MonsterBase::Update(float _Delta)
{
	Hit();
	Die();
}

void MonsterBase::Hit()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Col2->GetParentObject()->Off();
			float Dmg = StatManager::Inst->GetDamage(Col2);
			StatManager::Inst->ChangeHp(MonsterStat.get(), -Dmg);
			HitDmgEffController->StartEffect(Transform.GetWorldPosition() + float4(0,ImageSize.Y * 3/4), Dmg);
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(EnemyColOrder, Event);
}

void MonsterBase::Die()
{

}

