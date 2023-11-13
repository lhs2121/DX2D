#include "PreCompile.h"
#include "Boss_Vellum.h"
#include "DamageIndicator.h"
#include "Player.h"

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

		Renderer->CreateAnimation("Boss_Move", "Boss_Move", 0.1f, 0, 9, true);

		Renderer->CreateAnimation("Body_UpDown", "Body_UpDown", 0.1f, 0, 32, false);
		Renderer->CreateAnimation("Body_ShortUpDown", "Body_ShortUpDown", 0.1f, 0, 33, false);

		Renderer->CreateAnimation("Fire_Start", "Fire_Start", 0.1f, 0, 22, false);
		Renderer->CreateAnimation("Fire_CloseRange", "Fire_CloseRange", 0.1f, 0, 26, false);
		Renderer->CreateAnimation("Fire_LongRange", "Fire_LongRange", 0.1f, 0, 28, false);
		Renderer->CreateAnimation("Fire_MidRange", "Fire_MidRange", 0.1f, 0, 27, false);
		Renderer->CreateAnimation("Fire_End", "Fire_End", 0.1f, 0, 12, false);

		Renderer->CreateAnimation("Dive", "Dive", 0.1f, 0, 31, false);

		Renderer->CreateAnimation("Poison_Start", "Poison_Start", 0.1f, 0, 20, false);
		Renderer->CreateAnimation("Poison_Update", "Poison_Update", 0.1f, 0, 22, false);
		Renderer->CreateAnimation("Poison_End", "Poison_End", 0.1f, 0, 31, false);

		Renderer->CreateAnimation("Ult_Start", "Ult_Start", 0.1f, 0, 51, false);
		Renderer->CreateAnimation("Ult_Update", "Ult_Update", 0.1f, 0, 11, false);
		Renderer->CreateAnimation("Ult_End", "Ult_End", 0.1f, 0, 6, false);
		Renderer->CreateAnimation("Ult_Screen", "Ult_Screen", 0.1f, 0, 5, false);

		Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f, 0, 61, false);


		Renderer->Transform.SetLocalPosition({ 0,-70.0f });
		Renderer->AutoSpriteSizeOn();
	}

	ChangeState(BossState::Poison);
	Transform.SetWorldPosition({ 1695 ,-723 });
}
void Boss_Vellum::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Boss_Vellum::ChangeState(BossState _State)
{
	CurState = _State;

	switch (CurState)
	{
	case BossState::Move:
		MoveStart();
		break;
	case BossState::Body:
		BodyStart();
		break;
	case BossState::Fire:
		FireStart();
		break;
	case BossState::Dive:
		DiveStart();
		break;
	case BossState::Poison:
		PoisonStart();
		break;
	case BossState::Ult:
		UltStart();
		break;
	default:
		break;
	}

}

void Boss_Vellum::SetNextState()
{
	int RandomNumber = GameEngineRandom::GameEngineRandom().RandomInt(1, 100);
	int RangeStart = 1;
	int RangeEnd = 0;

	RangeEnd = RangeStart + BodyProb;
	if (RandomNumber >= RangeStart && RandomNumber < RangeEnd)
	{
		NextState = BossState::Body;
		return;
	}
	RangeStart = RangeEnd;

	// Fire
	RangeEnd = RangeStart + FireProb;
	if (RandomNumber >= RangeStart && RandomNumber < RangeEnd)
	{
		NextState = BossState::Fire;
		return;
	}
	RangeStart = RangeEnd;

	// Dive
	RangeEnd = RangeStart + DiveProb;
	if (RandomNumber >= RangeStart && RandomNumber < RangeEnd)
	{
		NextState = BossState::Dive;
		return;
	}
	RangeStart = RangeEnd;

	// Poison
	RangeEnd = RangeStart + PoisonProb;
	if (RandomNumber >= RangeStart && RandomNumber < RangeEnd)
	{
		NextState = BossState::Poison;
		return;
	}
	RangeStart = RangeEnd;

	// Ult
	RangeEnd = RangeStart + UltProb;
	if (RandomNumber >= RangeStart && RandomNumber <= RangeEnd)
	{
		NextState = BossState::Ult;
		return;
	}
}

void Boss_Vellum::SetDir()
{
	float Dir = Player::MainPlayer->Transform.GetWorldPosition().X - Transform.GetWorldPosition().X;
	if (Dir > 0)
	{
		Renderer->RightFlip();
	}
}

void Boss_Vellum::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BossState::Move:
		MoveUpdate(_Delta);
		break;
	case BossState::Body:
		BodyUpdate(_Delta);
		break;
	case BossState::Fire:
		FireUpdate(_Delta);
		break;
	case BossState::Dive:
		DiveUpdate(_Delta);
		break;
	case BossState::Poison:
		PoisonUpdate(_Delta);
		break;
	case BossState::Ult:
		UltUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Boss_Vellum::MoveStart()
{
	MoveDuration = GameEngineRandom::GameEngineRandom().RandomInt(1, 4);
	Renderer->ChangeAnimation("Boss_Move");
}
void Boss_Vellum::MoveUpdate(float _Delta)
{
	MoveDuration -= _Delta;
	if (MoveDuration <= 0)
	{
		MoveEnd();
	}

	float4 dir = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();
	dir.Normalize();
	Transform.AddWorldPosition({ dir.X * Speed * _Delta,0 });
}
void Boss_Vellum::MoveEnd()
{
	SetNextState();
	ChangeState(NextState);
}

// Body
void Boss_Vellum::BodyStart()
{
	Renderer->ChangeAnimation("Body_UpDown");
}
void Boss_Vellum::BodyUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		BodyEnd();
	}
}
void Boss_Vellum::BodyEnd()
{
	if (Renderer->IsCurAnimation("Body_UpDown"))
	{
		Renderer->ChangeAnimation("Body_ShortUpDown");
	}
	else if (Renderer->IsCurAnimation("Body_ShortUpDown"))
	{
		ChangeState(BossState::Move);
	}
}

//Fire
void Boss_Vellum::FireStart()
{
	Renderer->ChangeAnimation("Fire_Start");
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
	if (Renderer->IsCurAnimation("Fire_Start"))
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
		Renderer->ChangeAnimation("Fire_End");
	}
	else if (Renderer->IsCurAnimation("Fire_End"))
	{
		ChangeState(BossState::Move);
	}
}

void Boss_Vellum::PoisonStart()
{
	Renderer->ChangeAnimation("Poison_Start");
}
void Boss_Vellum::PoisonUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		PoisonEnd();
	}
}
void Boss_Vellum::PoisonEnd()
{
	if (Renderer->IsCurAnimation("Poison_Start"))
	{
		Renderer->ChangeAnimation("Poison_Update");
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 1)
	{
		Renderer->ChangeAnimation("Poison_Update");
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 2)
	{
		Renderer->ChangeAnimation("Poison_Update");
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 3)
	{
		Renderer->ChangeAnimation("Poison_End");
		PoisonAttackCount = 0;
	}
	else if (Renderer->IsCurAnimation("Poison_End"))
	{
		ChangeState(BossState::Move);
	}
}

void Boss_Vellum::DiveStart()
{
	float PlayerX = Player::MainPlayer->Transform.GetWorldPosition().X;
	float BossY = Transform.GetWorldPosition().Y;
	Transform.SetWorldPosition({ PlayerX,BossY });
	Renderer->ChangeAnimation("Dive");
}
void Boss_Vellum::DiveUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		DiveEnd();
	}
}
void Boss_Vellum::DiveEnd()
{
	ChangeState(BossState::Move);
}

void Boss_Vellum::UltStart()
{
}

void Boss_Vellum::UltUpdate(float _Delta)
{
}

void Boss_Vellum::UltEnd()
{
}

