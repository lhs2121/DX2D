#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"
#include "StatData.h"
#include "DamageIndicator.h"
#include "Item_Drop.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::ApplyDamage(std::vector<float> _DamageGroup)
{
	for (size_t i = 0; i < _DamageGroup.size(); i++)
	{
		Stat->CurHp -= _DamageGroup[i];
	}

	if (Stat->CurHp < 0)
	{
		AttackCol->Off();
	}
}

void Monster::RenderDamage(std::vector<float> _DamageGroup, int _DamageID, int _Order)
{
	float4 Pos = Transform.GetWorldPosition() + float4(0.0f, ImageSize.Y);
	DamageRenderer->PlusRenderOrder(_Order);
	DamageRenderer->RenderDamage(Pos, DamageColor::Red, _DamageGroup, _DamageID);

	if (CurState != MonsterState::DIE)
	{
		float4 dir = Transform.GetWorldPosition() - Player::MainPlayer->Transform.GetWorldPosition();
		dir.Normalize();
		NetForce.X = dir.X * 150.0f;
		DeathCheck();
	}
}

void Monster::DeathCheck()
{
	if (Stat->CurHp < 0)
	{
		ChangeState(MonsterState::DIE);
	}
}
;

void Monster::Start()
{
	MonsterBase::Start();
	{
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(155);
	}
}

void Monster::Update(float _Delta)
{
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

void Monster::DropItem()
{
	GetLevel()->CreateActor<Item_Drop>(500)->Setting(Transform.GetWorldPosition(), ItemName,30);
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
		dir = GameEngineRandom().RandomInt(-1, 1);
		DirCycleTime = 2.0f;
	}

	Transform.AddWorldPosition(float4(dir * Speed * _Delta, 0) );
}

void Monster::HitStart()
{
	Renderer->SetSprite(HitAniName);
	HitCoolTime = 0.2f;
}

void Monster::HitUpdate(float _Delta)
{
	HitCoolTime -= _Delta;
	if (HitCoolTime <= 0)
	{
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
		HitCol->Off();
	}

	if (Renderer->IsCurAnimationEnd())
	{
		DropItem();
		Death();
	}
}

void Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


