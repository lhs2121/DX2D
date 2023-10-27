#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	MonsterBase::Start();
}

void Monster::Update(float _Delta)
{
	MonsterBase::Update(_Delta);
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

void Monster::ChangeState(MonsterState _State)
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

void Monster::RunStart()
{
	Renderer->ChangeAnimation(IdleAniName);
}

void Monster::RunUpdate(float _Delta)
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

void Monster::HitStart()
{
	NetForce.X += 200.0f;
	Renderer->ChangeAnimation(HitAniName);
}

void Monster::HitUpdate(float _Delta)
{
	HitCoolTime -= _Delta;
	if (HitCoolTime <= 0)
	{
		HitCoolTime = 0.3f;
		ChangeState(MonsterState::RUN);
	}
}

void Monster::DieStart()
{
	Renderer->ChangeAnimation(DieAniName);
}

void Monster::DieUpdate(float _Delta)
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
