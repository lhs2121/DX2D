#include "PreCompile.h"
#include "Player.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
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

	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 500, -800, 0.0f });

}



void Player::StateCheck()
{
	if
	(
		(GameEngineInput::IsFree(VK_UP) && GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_DOWN) && GameEngineInput::IsFree(VK_RIGHT)) ||
		(GameEngineInput::IsPress(VK_LEFT) && GameEngineInput::IsPress(VK_RIGHT))
	)
	{
		ChangeState(PlayerState::IDLE);
	}
	else
	{
		ChangeState(PlayerState::RUN);
	}
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

void Player::ApplyGravity(float _Delta)
{
	float4 BottomPos = Transform.GetWorldPosition() + float4(0, -43);
	GameEngineColor Color = BackGround::MainMap->GetColor(BottomPos, GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GrivityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	else if(GameEngineColor::RED == Color)
	{
		GrivityForce = 0.0f;
	}
}


void Player::CameraFocus()
{
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}

void Player::Update(float _Delta)
{
	StateCheck();
	ApplyGravity(_Delta);
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
	case PlayerState::JUMP:
		JumpUpdate(_Delta);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Delta);
		break;
	default:
		break;
	}

	CameraFocus();
}

void Player::LevelStart(GameEngineLevel* _NextLevel)
{
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{
}


void Player::FlipRenderer()
{
	MainSpriteRenderer->Transform.SetLocalScale({ -MainSpriteRenderer->Transform.GetLocalScale().X,1.0f,1.0f });
}

void Player::AttackUpdate(float _Delta)
{
}



