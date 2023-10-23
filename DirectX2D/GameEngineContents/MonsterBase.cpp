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
	Renderer->CreateAnimation(HitAniName, HitAniName, 0.2f);
	Renderer->CreateAnimation(DieAniName, DieAniName, 0.3f);
	Renderer->ChangeAnimation(IdleAniName);
	Renderer->AutoSpriteSizeOn();

	ImageSize = Renderer->GetCurSprite().Texture->GetScale();

	Col->Transform.SetLocalScale(ImageSize);
	Col->Transform.SetLocalPosition({ 0,ImageSize.hY() });

	//TrackingCol->Transform.SetLocalScale({ ImageSize.X * 10,ImageSize.Y });
	//TrackingCol->Transform.SetLocalPosition({ 0,ImageSize.hY() });
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

	//{
	//	TrackingCol = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	//	TrackingCol->SetCollisionType(ColType::SPHERE2D);
	//}

	{
		MonsterStat = GetLevel()->CreateActor<MonsterStatData>(ActorOrder::MonsterStat);
	}
}


void MonsterBase::Update(float _Delta)
{
	ColCheck();
	
	switch (CurState)
	{
	case MonsterState::HIT:
		HitUpdate(_Delta);
		break;
	case MonsterState::RUN:
		RunUpdate(_Delta);
		break;
	case MonsterState::DIE:
		DieUpdate(_Delta);
		break;
	default:
		break;
	}
}

void MonsterBase::Release()
{
	HitDmgEffController->Death();
	HitDmgEffController = nullptr;
    MonsterStat->Death();
	MonsterStat = nullptr;
}

void MonsterBase::ChangeState(MonsterState _State)
{
	CurState = _State;
	switch (CurState)
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
	StatManager::Inst->ChangeExp(Player::MainPlayer->GetStat().get(), 30.0f);
	Renderer->ChangeAnimation(DieAniName);
}

void MonsterBase::HitUpdate(float _Delta)
{
	HitCoolTime -= _Delta;
	if (HitCoolTime <= 0)
	{
		HitCoolTime = 1.0f;
		ChangeState(MonsterState::RUN);
	}
	else if (MonsterStat->CurHp <= 0)
	{
		ChangeState(MonsterState::DIE);
	}
}

void MonsterBase::DieUpdate(float _Delta)
{
	if (Renderer->GetCurIndex() == 1)
	{
		Col->Off();
	}
	if (Renderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void MonsterBase::RunUpdate(float _Delta)
{
	DirCycleTime -= _Delta;
	if (DirCycleTime <= 0)
	{
		std::random_device rnd;
		GameEngineRandom random = GameEngineRandom();
		random.SetSeed(rnd());
		dir = random.RandomInt(-1, 1);
		DirCycleTime = 2.0f;
	}

	Transform.AddWorldPosition(float4(1,0) * dir * Speed * _Delta);
}

void MonsterBase::ColCheck()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Col2->GetParentObject()->Off();
			float Dmg = StatManager::Inst->GetDamage(Col2);
			HitDmgEffController->StartEffect(Transform.GetWorldPosition() + float4(0, ImageSize.Y * 3 / 4), Dmg);

			if (CurState != MonsterState::DIE)
			{
				StatManager::Inst->ChangeHp(MonsterStat.get(), -Dmg);
				ChangeState(MonsterState::HIT);
			}
			
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{

		};
	Col->CollisionEvent(EnemyColOrder, Event);
}

