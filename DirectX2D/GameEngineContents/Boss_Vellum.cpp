#include "PreCompile.h"
#include "Boss_Vellum.h"
#include "DamageEffectController.h"

Boss_Vellum::Boss_Vellum()
{
}

Boss_Vellum::~Boss_Vellum()
{
}

void Boss_Vellum::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
		Renderer->CreateAnimation("Body_UpDown","Body_UpDown");
		Renderer->CreateAnimation("Body_ShortUpDown", "Body_ShortUpDown");
		Renderer->Transform.SetLocalPosition({ 0,-80.0f });
		Renderer->AutoSpriteSizeOn();
		//Renderer->AnimationPauseOn();

	}
	{
		DamageViewer = GetLevel()->CreateActor<DamageEffectController>(ActorOrder::Manager);
	}

	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 400,500 });
		Col->Transform.SetLocalPosition({ 0,250 });
	}

	ChangeState(BossState::Body);
	Transform.SetWorldPosition({ 1695 ,-723 });

	GameEngineInput::AddInputObject(this);
}
void Boss_Vellum::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Boss_Vellum::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BossState::Body:
		BodyUpdate(_Delta);
		break;
	case BossState::Fire:
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

void Boss_Vellum::ChangeState(BossState _State)
{
	CurState = _State;

	switch (CurState)
	{
	case BossState::Body:
		BodyStart();
		break;
	case BossState::Fire:
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

void Boss_Vellum::BodyStart()
{
}

void Boss_Vellum::BodyUpdate(float _Delta)
{

	Renderer->ChangeAnimation("Body_ShortUpDown");
}

void Boss_Vellum::BodyEnd()
{
}

void Boss_Vellum::ColCheck()
{
	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col2)
		{
			Col2->GetActor()->GetDynamic_Cast_This<Player>()
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col2)
		{
		};
	Col->CollisionEvent(CollisionOrder::Player, Event);
}
