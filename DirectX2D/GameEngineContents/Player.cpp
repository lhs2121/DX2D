#include "PreCompile.h"
#include "Player.h"
#include "KCityMap.h"
#include "Monster.h"

Player::Player()
{
	CurState = PlayerState::IDLE;
	CurDirState = PlayerDirState::LEFT;
}

Player::~Player()
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		MainSpriteRenderer->SetSprite("idle");

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("Assets");
			Dir.MoveChild("Assets");
			Dir.MoveChild("Character");

			std::vector<GameEngineDirectory> DirGroup = Dir.GetAllDirectory();

			for (int i = 0; i < DirGroup.size(); i++)
			{
				std::string SpriteName = DirGroup[i].GetFileName();
				MainSpriteRenderer->CreateAnimation(SpriteName, SpriteName);
			}
		}

		MainSpriteRenderer->ChangeAnimation("idle");
		MainSpriteRenderer->SetRenderOrder(0);
		MainSpriteRenderer->SetPivotValue({ 0.5,0.71 });
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	{
		DebugRenderer0 = CreateComponent<GameEngineSpriteRenderer>(1);
		DebugRenderer0->SetRenderOrder(1);
		DebugRenderer0->SetSprite("etc");
	}

	{
		DebugRenderer1 = CreateComponent<GameEngineSpriteRenderer>(2);
		DebugRenderer1->SetRenderOrder(1);
		DebugRenderer1->SetSprite("etc", 1);
		DebugRenderer1->Transform.AddLocalPosition({ 0,1,0 });
	}

	{
		DebugRenderer2 = CreateComponent<GameEngineSpriteRenderer>(3);
		DebugRenderer2->SetRenderOrder(1);
		DebugRenderer2->SetSprite("etc", 2);
		DebugRenderer2->Transform.SetLocalPosition(RopePos);
	}

	{
		Col = CreateComponent<GameEngineCollision>(4);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 45,65 });
		Col->Transform.AddLocalPosition({ 0,35});
	}

	{
		CollisionRenderer = CreateComponent<GameEngineSpriteRenderer>(5);
		CollisionRenderer->SetRenderOrder(-1);
		CollisionRenderer->SetSprite("etc", 1);
		CollisionRenderer->SetImageScale(Col->Transform.GetLocalScale());
		CollisionRenderer->Transform.AddLocalPosition(Col->Transform.GetLocalPosition());
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 500, -900, 0.0f });
}

void Player::Update(float _Delta)
{
	DirUpdate();
	CameraFocus();
	HitUpdate();

	PhysicsActor::Update(_Delta);

	switch (CurState)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Delta);
		break;
	case PlayerState::RUN:
		RunUpdate(_Delta);
		break;
	case PlayerState::ROPE:
		RopeUpdate(_Delta);
		break;
	case PlayerState::DOWN:
		DownUpdate(_Delta);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Delta);
		break;
	default:
		break;
	}

	if (GameEngineInput::IsDown(VK_UP) && IsGrounded == true)
	{
		Jump();
	}
}

void Player::HitUpdate()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{
			Col->GetActor()->Death();
		};
	Col->CollisionEvent(ContentsCollisionType::Monster, Event);
}


void Player::DirUpdate()
{
	if ((GameEngineInput::IsFree(VK_RIGHT) && GameEngineInput::IsDown(VK_LEFT)) || (GameEngineInput::IsFree(VK_RIGHT) && GameEngineInput::IsPress(VK_LEFT)))
	{
		if (CurDirState == PlayerDirState::RIGHT)
		{
			FlipRenderer();
		}
		ChangeDirState(PlayerDirState::LEFT);
	}
	else if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsDown(VK_RIGHT) || (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsPress(VK_RIGHT)))
	{
		if (CurDirState == PlayerDirState::LEFT)
		{
			FlipRenderer();;
		}
		ChangeDirState(PlayerDirState::RIGHT);
	}
}

void Player::CameraFocus()
{
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}

void Player::FlipRenderer()
{
	MainSpriteRenderer->Transform.SetLocalScale({ -MainSpriteRenderer->Transform.GetLocalScale().X,1.0f,1.0f });
}




