#include "PreCompile.h"
#include "Player.h"
#include "LuckySeven.h"

void Player::ChangeState(PlayerState _State)
{
	CurState = _State;

	switch (CurState)
	{
	case PlayerState::IDLE:
		MainSpriteRenderer->ChangeAnimation("idle");
		break;
	case PlayerState::RUN:
		MainSpriteRenderer->ChangeAnimation("walk");
		break;
	case PlayerState::DOWN:
		MainSpriteRenderer->ChangeAnimation("down");
		break;
	case PlayerState::ROPE:
		MainSpriteRenderer->ChangeAnimation("rope");
		MainSpriteRenderer->AnimationPauseOn();
		break;
	case PlayerState::LUCKYSEVEN:
		ChangeRandomSwingAnimation();
		break;
	default:
		break;
	}
}

void Player::StateUpdate(float _Delta)
{
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
	case PlayerState::LUCKYSEVEN:
		LuckySevenUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::RUN);
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}
	else if (GameEngineInput::IsDown(VK_SHIFT) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
}

void Player::RunUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && IsGrounded == true && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (GameEngineInput::IsPress(VK_UP) && IsGrounded == false && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (GameEngineInput::IsDown(VK_SHIFT) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}

	if (CurDirState == PlayerDirState::LEFT)
	{
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			Transform.AddLocalPosition({ -Speed * _Delta, 0, 0 });
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			Transform.AddLocalPosition({ Speed * _Delta, 0, 0 });
		}
	}
	else if (CurDirState == PlayerDirState::RIGHT)
	{
		if (GameEngineInput::IsPress(VK_RIGHT))
		{
			Transform.AddLocalPosition({ Speed * _Delta, 0, 0 });
		}
		else if (GameEngineInput::IsPress(VK_LEFT))
		{
			Transform.AddLocalPosition({ -Speed * _Delta, 0, 0 });
		}
	}
}

void Player::RopeUpdate(float _Delta)
{
	static bool IsJoin = true;
	if (IsJoin == true)
	{
		if (IsGrounded == true)
		{
			Transform.AddWorldPosition({ 0,-2 });
		}
		else
		{
			Transform.AddWorldPosition({ 0, 2 });
		}

		ApplyGravity = false;
		IsJoin = false;
	}

	if ((CalCulateColor(Transform.GetWorldPosition() + float4(0, -1)) != GameEngineColor::GREEN &&
		CalCulateColor(Transform.GetWorldPosition() + float4(0, 40)) != GameEngineColor::GREEN))
	{
		ChangeState(PlayerState::IDLE);
		IsJoin = true;
		ApplyGravity = true;
		GravityForce.Y = -100.0f;
		MainSpriteRenderer->AnimationPauseOff();
		return;
	}

	if ((GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT)) && GameEngineInput::IsDown(VK_MENU))
	{
		ChangeState(PlayerState::RUN);
		IsJoin = true;
		ApplyGravity = true;
		GravityForce.Y = JumpForce;
		MainSpriteRenderer->AnimationPauseOff();
		return;
	}

	if (CurDirState == PlayerDirState::RIGHT)
	{
		FlipRenderer();
	}
	ChangeDirState(PlayerDirState::LEFT);

	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition({ 0, Speed * _Delta, 0 });
		MainSpriteRenderer->AnimationPauseOff();
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddLocalPosition({ 0,-Speed * _Delta, 0 });
		MainSpriteRenderer->AnimationPauseOff();
	}
}

void Player::DownUpdate(float _Delta)
{
	if (CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	if (GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (GameEngineInput::IsDown(VK_LEFT) || GameEngineInput::IsDown(VK_RIGHT))
	{
		ChangeState(PlayerState::RUN);
	}
}

void Player::MeleeAttackUpdate(float _Delta)
{
	MainSpriteRenderer->ChangeAnimation("stab1");
}

void Player::AutoAttackUpdate(float _Delta)
{
	MainSpriteRenderer->ChangeAnimation("swing1");
}

void Player::LuckySevenUpdate(float _Delta)
{
	if (MainSpriteRenderer->GetCurIndex() == 2)
	{
		LuckySeven::Inst->On();
	}
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
		{
			ChangeState(PlayerState::IDLE);
		}
		else if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
		{
			ChangeState(PlayerState::RUN);
		}
	}
}

void Player::ChangeRandomSwingAnimation()
{
	int RandomNumber = GameEngineRandom::GameEngineRandom().RandomInt(1, 3);
	std::string AnimationName = "swing" + std::to_string(RandomNumber);
	MainSpriteRenderer->ChangeAnimation(AnimationName);
}

