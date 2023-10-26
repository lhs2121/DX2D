#include "PreCompile.h"
#include "CombatActor.h"
#include "StatData.h"
#include "DamageActor.h"
#include "StatManager.h"
#include "DamageIndicator.h"

CombatActor::CombatActor()
{
}

CombatActor::~CombatActor()
{
}

void CombatActor::Start()
{
	DamageViewer = GetLevel()->CreateActor<DamageIndicator>();
}

void CombatActor::Update(float _Delta)
{
	if (MyStatData->CurHp < 0)
	{
		Die();
	}
	ColCheck();
}

void CombatActor::Release()
{
	if (DamageViewer != nullptr)
	{
		DamageViewer->Death();
		DamageViewer = nullptr;
	}

	if (Col != nullptr)
	{
		Col->Death();
		Col = nullptr;
	}

	if (MyStatData != nullptr)
	{
		MyStatData->Death();
		MyStatData = nullptr;
	}
}

void CombatActor::Hit()
{
}

void CombatActor::Die()
{
}

void CombatActor::CreateStatData(StatType _Type)
{
	CurStatType = _Type;
	switch (CurStatType)
	{
	case StatType::Player:
		MyStatData = GetLevel()->CreateActor<PlayerStatData>();
		break;
	case StatType::Monster:
		MyStatData = GetLevel()->CreateActor<MonsterStatData>();
		break;
	case StatType::Boss:
		MyStatData = GetLevel()->CreateActor<MonsterStatData>();
		break;
	default:
		break;
	}
}

void CombatActor::ColCheck()
{
	if (CurStatType == StatType::Player)
	{
		PlayerColUpdate();
	}
	else
	{
		MonsterColUpdate();
	}
}

void CombatActor::PlayerColUpdate()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* EnemyCol)
		{
			StatManager::Inst->ChangeHp(MyStatData->GetDynamic_Cast_This<PlayerStatData>(), 10);
			DamageViewer->StartSkill(Transform.GetWorldPosition(), 10, DamageColor::Purple);
		};
	Col->CollisionEvent(CollisionOrder::Monster, Event);
}

void CombatActor::MonsterColUpdate()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* EnemyCol)
		{
			std::shared_ptr<DamageActor> damageActor = EnemyCol->GetParentObject()->GetDynamic_Cast_This<DamageActor>();
			float Damage = damageActor->GetDamage();
			damageActor->Hit();
			Hit();
			StatManager::Inst->ChangeHp(MyStatData->GetDynamic_Cast_This<MonsterStatData>(), Damage);
			DamageViewer->StartSkill(Transform.GetWorldPosition(), Damage, DamageColor::Orange);
		};
	Col->CollisionEvent(CollisionOrder::PlayerSkill, Event);

}
