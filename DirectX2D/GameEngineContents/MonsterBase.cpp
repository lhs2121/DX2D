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

void MonsterBase::Setting(std::string MonsterName)
{
	IdleAniName = MonsterName + "Idle";
	HitAniName = MonsterName + "Hit";
	DieAniName = MonsterName + "Die";

	Renderer->CreateAnimation(IdleAniName, IdleAniName, 0.2f);
	Renderer->CreateAnimation(HitAniName, IdleAniName, 0.2f);
	Renderer->CreateAnimation(DieAniName, IdleAniName, 0.2f);
	Renderer->ChangeAnimation(IdleAniName);
	Renderer->AutoSpriteSizeOn();

	ImageSize = Renderer->GetCurSprite().Texture->GetScale();

	Col->Transform.SetLocalScale(ImageSize);
	Col->Transform.SetLocalPosition({ 0,ImageSize.hY() });
}

void MonsterBase::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
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
	switch (CurState)
	{
	case MonsterState::HIT:
		HitUpdate();
		break;
	case MonsterState::RUN:
		RunUpdate(_Delta);
		break;
	case MonsterState::DIE:
		DieUpdate();
		break;
	default:
		break;
	}
}

void MonsterBase::ChangeState(MonsterState _State)
{
	switch (_State)
	{
	case MonsterState::HIT:
		HitStart();
		break;
	case MonsterState::RUN:
		RunStart();
		break;
	case MonsterState::DIE:
		DieStart();
		break;
	default:
		break;
	}
}

void MonsterBase::HitUpdate()
{
	if (MonsterStat->CurHp <= 0)
	{
		ChangeState(MonsterState::DIE);
	}
}

void MonsterBase::DieUpdate()
{
	
}

void MonsterBase::RunUpdate(float _Delta)
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Col2->GetParentObject()->Off();
			float Dmg = StatManager::Inst->GetDamage(Col2);
			StatManager::Inst->ChangeHp(MonsterStat.get(), -Dmg);
			HitDmgEffController->StartEffect(Transform.GetWorldPosition() + float4(0, ImageSize.Y * 3 / 4), Dmg);
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(EnemyColOrder, Event);

	if (MonsterStat->CurHp <= 0)
	{
		ChangeState(MonsterState::DIE);
	}

	DirCycleTime -= _Delta;
	if (DirCycleTime <= 0)
	{
		dir = GameEngineRandom::GameEngineRandom().RandomInt(-1, 1);
		DirCycleTime = 2.0f;
	}

	Transform.AddWorldPosition(float4(1,0) * dir * Speed * _Delta);
}

void MonsterBase::HitStart()
{
	Renderer->ChangeAnimation(HitAniName);
}

void MonsterBase::RunStart()
{
	Renderer->ChangeAnimation(RunAniName);
}

void MonsterBase::DieStart()
{
	Renderer->ChangeAnimation(DieAniName);
}
