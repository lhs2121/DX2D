#include "PreCompile.h"
#include "Boss_Vellum.h"
#include "DamageEffectController.h"
#include "Player.h"
#include "StatData.h"
#include "StatManager.h"

Boss_Vellum::Boss_Vellum()
{
}

Boss_Vellum::~Boss_Vellum()
{
}

void Boss_Vellum::Start()
{
	{
		BossStat = GetLevel()->CreateActor<MonsterStatData>(ActorOrder::MonsterStat);
	}

	{
		DamageViewer = GetLevel()->CreateActor<DamageEffectController>(ActorOrder::Manager);
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);

		Renderer->CreateAnimation("Body_Up", "Body_Up");
		Renderer->CreateAnimation("Body_End", "Body_End");

		Renderer->CreateAnimation("Body_Move", "Body_Move");
		Renderer->CreateAnimation("Body_UpDown", "Body_UpDown");
		Renderer->CreateAnimation("Body_ShortUpDown", "Body_ShortUpDown");

		Renderer->CreateAnimation("Fire_CloseRange", "Fire_CloseRange");
		Renderer->CreateAnimation("Fire_LongRange", "Fire_LongRange");
		Renderer->CreateAnimation("Fire_MidRange", "Fire_MidRange");
		

		Renderer->Transform.SetLocalPosition({ 0,-70.0f });
		Renderer->AutoSpriteSizeOn();
	}

	{
	    BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		BodyCol->SetCollisionType(ColType::AABBBOX2D);
		BodyCol->Transform.SetLocalScale({ 400,500 });
		BodyCol->Transform.SetLocalPosition({ 0,250 });
	}

	ChangeState(BossState::Body);
	Transform.SetWorldPosition({ 1695 ,-723 });
}
void Boss_Vellum::Update(float _Delta)
{
	ColCheck();
	StateUpdate(_Delta);
}

void Boss_Vellum::ChangeState(BossState _State)
{
	CurState = _State;

	switch (CurState)
	{
	case BossState::Body:
		BodyStart();
		break;
	case BossState::Fire:
		FireStart();
		break;
	case BossState::Dive:
		break;
	case BossState::Poison:
		break;
	case BossState::Ult:
		break;
	default:
		break;
	}

}

void Boss_Vellum::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BossState::Body:
		BodyUpdate(_Delta);
		break;
	case BossState::Fire:
		FireUpdate(_Delta);
		break;
	case BossState::Dive:
		break;
	case BossState::Poison:
		break;
	case BossState::Ult:
		break;
	default:
		break;
	}
}

// Move
void Boss_Vellum::BodyStart()
{
	Renderer->ChangeAnimation("Body_Move");
}
void Boss_Vellum::BodyUpdate(float _Delta)
{
	if (Renderer->IsCurAnimation("Body_Move"))
	{
		float4 dir = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();
		dir.Normalize();

		Transform.AddWorldPosition({ dir.X * Speed * _Delta,0 });
	}

	if (Renderer->IsCurAnimationEnd())
	{
		BodyEnd();
	}
}

void Boss_Vellum::BodyEnd()
{
	if (Renderer->IsCurAnimation("Body_Move"))
	{
		Renderer->ChangeAnimation("Body_UpDown");
	}
	else if (Renderer->IsCurAnimation("Body_UpDown"))
	{
		Renderer->ChangeAnimation("Body_ShortUpDown");
	}
	else if (Renderer->IsCurAnimation("Body_ShortUpDown"))
	{
		ChangeState(BossState::Fire);
	}
}

//Fire
void Boss_Vellum::FireStart()
{
	Renderer->ChangeAnimation("Body_Up");
}

void Boss_Vellum::FireUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		FireEnd();
	}
}

void Boss_Vellum::FireEnd()
{
	if (Renderer->IsCurAnimation("Body_Up"))
	{
		Renderer->ChangeAnimation("Fire_CloseRange");
	}
	else if (Renderer->IsCurAnimation("Fire_CloseRange"))
	{
		Renderer->ChangeAnimation("Fire_MidRange");
	}
	else if (Renderer->IsCurAnimation("Fire_MidRange"))
	{
		Renderer->ChangeAnimation("Fire_LongRange");
	}
	else if (Renderer->IsCurAnimation("Fire_LongRange"))
	{
		Renderer->ChangeAnimation("Body_End");
	}
	else if (Renderer->IsCurAnimation("Body_End"))
	{
		ChangeState(BossState::Body);
	}
}


void Boss_Vellum::ColCheck()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Col2->GetParentObject()->Off();
			float Dmg = StatManager::Inst->GetDamage(Col2);
			DamageViewer->StartEffect(Transform.GetWorldPosition(), Dmg);
			StatManager::Inst->ChangeHp(BossStat.get(), -Dmg);
			
		};
	BodyCol->CollisionEvent(CollisionOrder::PlayerWeapon, Event);
}
