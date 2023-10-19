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
		Col->Transform.SetLocalScale({ 50,50 });
		Col->Transform.SetLocalPosition({ 0,50 });
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
			float Dmg = StatManager::Inst->GetDamage(Col2);
			StatManager::Inst->ChangeHp(MonsterStat.get(), -Dmg);
			HitDmgEffController->StartEffect(Transform.GetWorldPosition() + float4(-70.0f, 70.0f), Dmg);
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
	if(MonsterStat->CurHp < 0)
	{
		Death();
	}
}

