#include "PreCompile.h"
#include "Boss_Vellum.h"
#include "DamageIndicator.h"
#include "PoisonArea.h"
#include "Player.h"
#include "MapleMap.h"
#include "UI_Boss_HpBar.h"

Boss_Vellum::Boss_Vellum()
{
}

Boss_Vellum::~Boss_Vellum()
{
}

void Boss_Vellum::RenderDamage(std::vector<float> _DamageGroup, int _DamageID, int _Order)
{
	float4 Pos = Transform.GetWorldPosition() + float4(0.0f,500.0f);
	DamageRenderer->PlusRenderOrder(_Order);
	DamageRenderer->RenderDamage(Pos, DamageColor::Red, _DamageGroup, _DamageID);
}

void Boss_Vellum::ApplyDamage(std::vector<float> _DamageGroup)
{
	for (size_t i = 0; i < _DamageGroup.size(); i++)
	{
		CurHp -= _DamageGroup[i];
		float a = 758.0f / MaxHp;
		float ConvertedValue = _DamageGroup[i] * a;
		HpBar->AddHpGauge(-ConvertedValue);
	}

	if (CurHp < 0)
	{
		ChangeState(BossState::Die);
	}
}

void Boss_Vellum::Start()
{
	{
		HpBar = GetLevel()->CreateActor<UI_Boss_HpBar>();
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);

		Renderer->CreateAnimation("Boss_Move", "Boss_Move", 0.1f, 0, 9, true);

		Renderer->CreateAnimation("Body_UpDown", "Body_UpDown", 0.1f, 0, 32, false);
		Renderer->SetFrameEvent("Body_UpDown", 16, [&](GameEngineSpriteRenderer*)
			{
				Col->On();
				BodyCol->On(); 
			});
		Renderer->SetFrameEvent("Body_UpDown", 19, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off(); 
			});
		Renderer->SetEndEvent("Body_UpDown", [&](GameEngineSpriteRenderer*)
			{
				Col->Off();
			});

		Renderer->CreateAnimation("Body_ShortUpDown", "Body_ShortUpDown", 0.1f, 0, 33, false);
		Renderer->SetFrameEvent("Body_ShortUpDown", 16, [&](GameEngineSpriteRenderer*)
			{
				Col->On();
				BodyCol->On(); 
			});
		Renderer->SetFrameEvent("Body_ShortUpDown", 19, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off(); 
			});
		Renderer->SetEndEvent("Body_ShortUpDown", [&](GameEngineSpriteRenderer*)
			{
				Col->Off();
			});

		Renderer->CreateAnimation("Fire_Start", "Fire_Start", 0.1f, 0, 22, false);
		Renderer->SetFrameEvent("Fire_Start", 16, [&](GameEngineSpriteRenderer*)
			{
				Col->On();
				BodyCol->On(); 
			});
		Renderer->SetFrameEvent("Fire_Start", 19, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off();
			});

		Renderer->CreateAnimation("Fire_CloseRange", "Fire_CloseRange", 0.1f, 0, 26, false);
		Renderer->SetFrameEvent("Fire_CloseRange", 16, [&](GameEngineSpriteRenderer*)
			{
				FireCol->On(); 
			});
		Renderer->SetFrameEvent("Fire_CloseRange", 19, [&](GameEngineSpriteRenderer*)
			{
				FireCol->Off();
			});

		Renderer->CreateAnimation("Fire_LongRange", "Fire_LongRange", 0.1f, 0, 28, false);
		Renderer->SetFrameEvent("Fire_LongRange", 16, [&](GameEngineSpriteRenderer*)
			{
				FireCol->On();
			});
		Renderer->SetFrameEvent("Fire_LongRange", 19, [&](GameEngineSpriteRenderer*)
			{
				FireCol->Off(); 
			});

		Renderer->CreateAnimation("Fire_MidRange", "Fire_MidRange", 0.1f, 0, 27, false);
		Renderer->SetFrameEvent("Fire_MidRange", 16, [&](GameEngineSpriteRenderer*)
			{
				FireCol->On();
			});
		Renderer->SetFrameEvent("Fire_MidRange", 19, [&](GameEngineSpriteRenderer*)
			{
				FireCol->Off(); 
			});

		Renderer->CreateAnimation("Fire_End", "Fire_End", 0.1f, 0, 12, false);
		Renderer->SetFrameEvent("Fire_End", 6, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->On();
			});
		Renderer->SetFrameEvent("Fire_End", 9, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off();
			});
		Renderer->SetEndEvent("Fire_End", [&](GameEngineSpriteRenderer*)
			{
				Col->Off();
			});

		Renderer->CreateAnimation("Dive", "Dive", 0.1f, 0, 31, false);

		Renderer->CreateAnimation("Poison_Start", "Poison_Start", 0.1f, 0, 20, false);
		Renderer->SetFrameEvent("Poison_Start", 14, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->On();
				Col->On();
			});
		Renderer->SetFrameEvent("Poison_Start", 17, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off();
			});

		Renderer->CreateAnimation("Poison_Update", "Poison_Update", 0.1f, 0, 22, false);
		Renderer->SetFrameEvent("Poison_Update", 15, [&](GameEngineSpriteRenderer*)
			{
				PoisonSetting();
			});

		Renderer->CreateAnimation("Poison_End", "Poison_End", 0.1f, 0, 31, false);
		Renderer->SetFrameEvent("Poison_End", 25, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->On();
			});
		Renderer->SetFrameEvent("Poison_End", 27, [&](GameEngineSpriteRenderer*)
			{
				BodyCol->Off();
			});
		Renderer->SetEndEvent("Poison_End", [&](GameEngineSpriteRenderer*)
			{
				Col->Off();
			});

		Renderer->CreateAnimation("Ult_Start", "Ult_Start", 0.1f, 0, 51, false);
		Renderer->CreateAnimation("Ult_Update", "Ult_Update", 0.1f, 0, 11, true);
		Renderer->CreateAnimation("Ult_End", "Ult_End", 0.1f, 0, 20, false);

		Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f, 0, 61, false);

		Renderer->Transform.SetLocalPosition({ 0,-70.0f });
		Renderer->AutoSpriteSizeOn();
	}

	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Boss);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale(BodyColScale);
		Col->Off();

		BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::BossAttack);
		BodyCol->SetCollisionType(ColType::AABBBOX2D);
		BodyCol->Transform.SetLocalScale(BodyColScale);
		BodyCol->Off();

		FireCol = CreateComponent<GameEngineCollision>(CollisionOrder::BossAttack);
		FireCol->SetCollisionType(ColType::AABBBOX2D);
		FireCol->Transform.SetLocalScale(FireColScale);
		FireCol->Off();

	}

	{
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(ActorOrder::Manager);
	}

	{
		PoisonAreas.reserve(30);
		for (size_t i = 0; i < 30; i++)
		{
			PoisonAreas.push_back(GetLevel()->CreateActor<PoisonArea>());
		}
	}

	{
		UltScreenRenderer.reserve(6);

		for (size_t i = 0; i < 6; i++)
		{
			std::shared_ptr<GameEngineSpriteRenderer> NewRenderer;
			NewRenderer = CreateComponent<GameEngineSpriteRenderer>();
			NewRenderer->SetRenderOrder(RenderOrder::Effect);
			NewRenderer->SetPivotType(PivotType::Right);
			NewRenderer->CreateAnimation("Ult_Screen", "Ult_Screen");
			NewRenderer->ChangeAnimation("Ult_Screen");
			NewRenderer->AutoSpriteSizeOn();
			NewRenderer->Off();

			UltScreenRenderer.push_back(NewRenderer);
		}
	}
	GameEngineInput::AddInputObject(this);
	Transform.SetWorldPosition({ 1695 ,-723 });
}
void Boss_Vellum::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Boss_Vellum::ChangeState(BossState _State)
{
	PrevState = CurState;
	CurState = _State;

	SetRendererDir();

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
	case BossState::Die:
		DieStart();
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

void Boss_Vellum::SetRendererDir()
{
	Dir = Player::MainPlayer->Transform.GetWorldPosition().X - Transform.GetWorldPosition().X;

	if (Dir > 0)
	{
		Renderer->Transform.SetLocalScale({ -1,1 });
	}
	else
	{
		Renderer->Transform.SetLocalScale({ 1,1 });
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
	case BossState::Die:
		DieUpdate(_Delta);
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
		if (Dir < 0)
		{
			FireCol->Transform.SetLocalPosition(LeftClosePos);
		}
		else
		{
			FireCol->Transform.SetLocalPosition(RightClosePos);
		}

		Renderer->ChangeAnimation("Fire_CloseRange");
	}
	else if (Renderer->IsCurAnimation("Fire_CloseRange"))
	{
		if (Dir < 0)
		{
			FireCol->Transform.SetLocalPosition(LeftMidPos);
		}
		else
		{
			FireCol->Transform.SetLocalPosition(RightMidPos);
		}

		Renderer->ChangeAnimation("Fire_MidRange");
	}
	else if (Renderer->IsCurAnimation("Fire_MidRange"))
	{
		if (Dir < 0)
		{
			FireCol->Transform.SetLocalPosition(LeftLongPos);
		}
		else
		{
			FireCol->Transform.SetLocalPosition(RightLongPos);
		}

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
	PoisonInterTime = 0.0f;
	Renderer->ChangeAnimation("Poison_Start");
}
void Boss_Vellum::PoisonUpdate(float _Delta)
{
	PoisonInterTime -= _Delta;

	if (Renderer->IsCurAnimationEnd() && PoisonInterTime <= 0)
	{
		PoisonEnd();
	}
}
void Boss_Vellum::PoisonEnd()
{
	if (Renderer->IsCurAnimation("Poison_Start"))
	{
		PoisonInterTime = 0.0f;

		Renderer->ChangeAnimation("Poison_Update");
		Renderer->CurAnimation()->Reset();
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 1)
	{
		PoisonInterTime = 3.0f;

		Renderer->ChangeAnimation("Poison_Update");
		Renderer->CurAnimation()->Reset();
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 2)
	{
		PoisonInterTime = 3.0f;

		Renderer->ChangeAnimation("Poison_Update");
		Renderer->CurAnimation()->Reset();
		PoisonAttackCount += 1;
	}
	else if (Renderer->IsCurAnimation("Poison_Update") && PoisonAttackCount == 3)
	{
		PoisonInterTime = 3.0f;

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
	Transform.SetWorldPosition(RightUltPos);
	for (size_t i = 0; i < UltScreenRenderer.size(); i++)
	{
		UltScreenRenderer[i]->Transform.SetWorldPosition({ 1915.482788 ,-338.022339 });
		UltScreenRenderer[i]->Transform.AddWorldPosition({-340.0f * i,0});
	}

	Renderer->ChangeAnimation("Ult_Start");
}

void Boss_Vellum::UltUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		UltEnd();
	}
}

void Boss_Vellum::UltEnd()
{
	if (Renderer->IsCurAnimation("Ult_Start"))
	{
		Renderer->ChangeAnimation("Ult_Update");
	
		for (size_t i = 0; i < UltScreenRenderer.size(); i++)
		{
			UltScreenRenderer[i]->On();
		}
	}
	else if (Renderer->IsCurAnimation("Ult_Update"))
	{
		UltAttackCount++;
		if (UltAttackCount == 5)
		{
			for (size_t i = 0; i < UltScreenRenderer.size(); i++)
			{
				UltScreenRenderer[i]->Off();
			}
			Renderer->ChangeAnimation("Ult_End");
		}
	}
	else if (Renderer->IsCurAnimation("Ult_End"))
	{
		UltAttackCount = 0;
		ChangeState(BossState::Move);
	}
}

void Boss_Vellum::DieStart()
{
	HpBar->Death();
	if (PrevState == BossState::Poison)
	{
		Renderer->ChangeAnimation("Poison_End");
	}
	else
	{
		Renderer->ChangeAnimation("Fire_End");
	}
}

void Boss_Vellum::DieUpdate(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		DieEnd();
	}
}

void Boss_Vellum::DieEnd()
{
	if (Renderer->IsCurAnimation("Boss_Die") == false) 
	{
		Renderer->ChangeAnimation("Boss_Die");
	}
	else
	{
		Death();
	}
}

void Boss_Vellum::PoisonSetting()
{
	std::vector<std::shared_ptr<PoisonArea>> Temp;
	for (size_t i = 0; i < PoisonAreas.size(); i++)
	{
		if (PoisonAreas[i]->IsUpdate() == false)
		{
			Temp.push_back(PoisonAreas[i]);
		}

		if (Temp.size() == 10)
		{
			break;
		}
	}

	float MapScaleX = MapleMap::CurMap->GetMapScale().X;
	for (int i = 0; i < Temp.size(); i++)
	{
		float rd = GameEngineRandom::GameEngineRandom().RandomFloat(0.9f, 1.1f);
		float devide = static_cast<float>(i) / 10.0f;
		float4 SpawnPos = float4(MapScaleX * devide * rd, Transform.GetWorldPosition().Y - 5.0f);
		Temp[i]->Transform.SetWorldPosition(SpawnPos);
		Temp[i]->On();
	}
}

void Boss_Vellum::LevelStart(GameEngineLevel* _PrevLevel)
{
	float MapScaleX = MapleMap::CurMap->GetMapScale().X;
	RightUltPos = float4(MapScaleX - 500.0f, -723.0f);
	LeftUltPos = { 500.0f,-723.0f };
	ChangeState(BossState::Ult);
}

void Boss_Vellum::LevelEnd(GameEngineLevel* _NextLevel)
{
}

