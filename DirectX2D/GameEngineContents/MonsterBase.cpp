#include "PreCompile.h"
#include "MonsterBase.h"
#include "StatData.h"
#include "Player.h"
#include "CombatActor.h"
#include "StatManager.h"


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
	Col->Transform.AddLocalPosition({ 0,ImageSize.hY()});

	On();
}

void MonsterBase::Start()
{
	CombatActor::Start();
	CreateStatData(StatType::Monster);

	Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	Col->SetCollisionType(ColType::AABBBOX2D);
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
	}

	Off();
}


void MonsterBase::Update(float _Delta)
{
	CombatActor::Update(_Delta);
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
	CombatActor::Release();
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

void MonsterBase::RunStart()
{
	Renderer->ChangeAnimation(IdleAniName);
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

	Transform.AddWorldPosition(float4(1, 0) * dir * Speed * _Delta);
}

void MonsterBase::HitStart()
{
	NetForce.X += 200.0f;
	Renderer->ChangeAnimation(HitAniName);
}

void MonsterBase::HitUpdate(float _Delta)
{
	HitCoolTime -= _Delta;
	if (HitCoolTime <= 0)
	{
		HitCoolTime = 0.3f;
		ChangeState(MonsterState::RUN);
	}
}

void MonsterBase::DieStart()
{
	Renderer->ChangeAnimation(DieAniName);
}

void MonsterBase::DieUpdate(float _Delta)
{
	if (Renderer->GetCurIndex() == 1)
	{
		Col->Off();
		
	}
	if (Renderer->IsCurAnimationEnd())
	{
		StatManager::Inst->ChangeExp(51);
		Death();
	}
}

void MonsterBase::Hit()
{
	ChangeState(MonsterState::HIT);
}

void MonsterBase::Die()
{
	ChangeState(MonsterState::DIE);
}




