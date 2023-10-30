#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "StatData.h"
#include "DamageIndicator.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::PushDamage(std::vector<float> _DamageGroup, int _DamageID)
{
	float4 Pos = Transform.GetWorldPosition() + float4(0.0f, ImageSize.Y);
	DamageRenderer->RenderDamage(Pos, DamageColor::Orange, _DamageGroup, _DamageID);
};

void Monster::Start()
{
	MonsterBase::Start();
	{
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(155);
	}
}

void Monster::Update(float _Delta)
{
	/*GameEngineInput::AddInputObject(this);
	if (InputIsDown('M'))
	{
		std::vector<float> _DamageGroup = { 2223,3223,13123,1215,535645,2323,6143 };
		DamageRenderer->RenderDamage(Transform.GetWorldPosition(), DamageColor::Orange, _DamageGroup);
	}*/
	
	PhysicsActor::Update(_Delta);
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

void Monster::Release()
{
	MonsterBase::Release();
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
	Col->Collision(CollisionOrder::PlayerSkill, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
		{
			float4 dir = Transform.GetWorldPosition() - Player::MainPlayer->Transform.GetWorldPosition();
			dir.Normalize();
			NetForce.X = dir.X * 100.0f;
			HitCoolTime = 0.15f;
			ChangeState(MonsterState::HIT);
		});

	DirCycleTime -= _Delta;
	if (DirCycleTime <= 0)
	{
		dir = GameEngineRandom().RandomInt(-1,1);
		DirCycleTime = 2.0f;
	}

	Transform.AddWorldPosition(float4(1, 0) * dir * Speed * _Delta);
}

void Monster::HitStart()
{
	Renderer->SetSprite(HitAniName);
}

void Monster::HitUpdate(float _Delta)
{
	if (Stat->CurHp < 0)
	{
		ChangeState(MonsterState::DIE);
	}

	Col->Collision(CollisionOrder::PlayerSkill, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
		{
			float4 dir = Transform.GetWorldPosition() - Player::MainPlayer->Transform.GetWorldPosition();
			dir.Normalize();
			NetForce.X = dir.X * 100.0f;
			HitCoolTime = 0.15f;
		});

	HitCoolTime -= _Delta;
	if (HitCoolTime <= 0)
	{
		HitCoolTime = 0.15f;
		ChangeState(MonsterState::RUN);
	}
}

void Monster::DieStart()
{
	Renderer->ChangeAnimation(DieAniName);
}

void Monster::DieUpdate(float _Delta)
{
	Renderer->GetColorData().MulColor.A -= _Delta;

	if (Renderer->GetCurIndex() == 1)
	{
		Col->Off();
	}
	
	if (Renderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


