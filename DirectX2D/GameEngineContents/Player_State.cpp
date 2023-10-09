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
	case PlayerState::WALK:
		MainSpriteRenderer->ChangeAnimation("walk");
		break;
	case PlayerState::JUMP:
		MainSpriteRenderer->ChangeAnimation("jump");
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
	case PlayerState::WALK:
		WalkUpdate(_Delta);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Delta);
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
		ChangeState(PlayerState::WALK);
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}
	else if (GameEngineInput::IsDown(VK_SHIFT) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
}

void Player::WalkUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && IsGrounded == true && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
	else if (GameEngineInput::IsPress(VK_UP) && IsGrounded == false && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (GameEngineInput::IsDown(VK_SHIFT) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
}

void Player::JumpUpdate(float _Delta)
{
	if (NetForce.Y == 0 && IsGrounded == true)
	{
		if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
		{
			ChangeState(PlayerState::IDLE);
		}
		if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
		{
			ChangeState(PlayerState::WALK);
		}
	}

	if (GameEngineInput::IsDown(VK_SHIFT) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
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

		ApplyForce = false;
		IsJoin = false;
	}

	if ((CalCulateColor(Transform.GetWorldPosition() + float4(0, -1)) != GameEngineColor::GREEN &&
		CalCulateColor(Transform.GetWorldPosition() + float4(0, 40)) != GameEngineColor::GREEN))
	{
		ChangeState(PlayerState::IDLE);
		IsJoin = true;
		ApplyForce = true;
		NetForce.Y = -100.0f;
		MainSpriteRenderer->AnimationPauseOff();
		return;
	}

	if ((GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT)) && GameEngineInput::IsDown(VK_MENU))
	{
		ChangeState(PlayerState::WALK);
		IsJoin = true;
		ApplyForce = true;
		NetForce.Y = JumpForce;
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
		ChangeState(PlayerState::WALK);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
}

void Player::LuckySevenUpdate(float _Delta)
{
	if (NetForce.Y == 0 && IsGrounded == true)
	{
		ApplyXForce = false;
	}
	
	if (MainSpriteRenderer->GetCurIndex() == 2)
	{
		LuckySeven::Inst->On();
	}
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
		{
			ApplyXForce = true;
			ChangeState(PlayerState::IDLE);
		}
		else if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
		{
			ApplyXForce = true;
			ChangeState(PlayerState::WALK);
		}
	}
}

void Player::MeleeAttackUpdate(float _Delta)
{
	
}

void Player::AutoAttackUpdate(float _Delta)
{
	
}
