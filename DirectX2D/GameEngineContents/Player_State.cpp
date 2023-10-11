#include "PreCompile.h"
#include "Player.h"
#include "LuckySeven.h"

void Player::ChangeState(PlayerState _State)
{
	CurState = _State;
	CanFlip = true;
	DirCheck = true;
	ApplyForce = true;
	ApplyXForce = true;
	ApplyGForce = true;

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
		ApplyXForce = false;
		CanFlip = false;
		MainSpriteRenderer->ChangeAnimation("down");
		break;
	case PlayerState::ROPE:
		ApplyForce = false;
		CanFlip = false;
		RopeStart();
		MainSpriteRenderer->ChangeAnimation("rope");
		MainSpriteRenderer->AnimationPauseOn();
		break;
	case PlayerState::LUCKYSEVEN:
		ApplyGForce = false;
		CanFlip = false;
		DirCheck = false;
		ChangeRandomSwingAnimation();
		break;
	default:
		break;
	}
}

void Player::RopeStart()
{
	NetForce = 0.0f;
	if (IsGrounded == true && GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0, -5 });
	}
	else if(IsGrounded == true && GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, 5 });
	}
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::WALK);
	}
	else if (GameEngineInput::IsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
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
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
	//else if (GameEngineInput::IsPress(VK_DOWN) && CanRope == false)
	//{
	//	ChangeState(PlayerState::DOWN);
	//}
	else if (GameEngineInput::IsPress(VK_DOWN) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (GameEngineInput::IsPress(VK_UP) && CanRope == true)
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
	else if (GameEngineInput::IsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
}

void Player::RopeUpdate(float _Delta)
{
	NetForce = 0.0f;
	if (CurDirState == PlayerDirState::RIGHT)
	{
		ChangeDirState(PlayerDirState::LEFT);
		FlipRenderer();
	}

	MainSpriteRenderer->AnimationPauseOn();

	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition({ 0, Speed * _Delta, 0 });
		MainSpriteRenderer->AnimationPauseOff();

		GameEngineColor TopColor = GetColor(Transform.GetWorldPosition() + float4(0, 65));
		GameEngineColor BottomColor = GetColor(Transform.GetWorldPosition() + float4(0, -1));

		if (TopColor != GameEngineColor::GREEN && BottomColor != GameEngineColor::GREEN)
		{
			ChangeState(PlayerState::IDLE);
			NetForce.Y = -100.0f;
			MainSpriteRenderer->AnimationPauseOff();
		}
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddLocalPosition({ 0,-Speed * _Delta, 0 });
		MainSpriteRenderer->AnimationPauseOff();

		GameEngineColor TopColor = GetColor(Transform.GetWorldPosition() + float4(0, 65));
		GameEngineColor BottomColor = GetColor(Transform.GetWorldPosition() + float4(0, -1));

		if (BottomColor != GameEngineColor::GREEN)
		{
			ChangeState(PlayerState::IDLE);
			NetForce.Y = -100.0f;
			MainSpriteRenderer->AnimationPauseOff();
		}
	}

	if ((GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT)) && GameEngineInput::IsDown(VK_MENU))
	{
		ChangeState(PlayerState::JUMP);
		NetForce.Y = 250.0f;
		MainSpriteRenderer->AnimationPauseOff();
	}
	if ((GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
		&& GameEngineInput::IsPress(VK_UP) 
		&& GameEngineInput::IsDown(VK_MENU))
	{
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			Transform.AddWorldPosition({ -3.0f,0.0f });
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			Transform.AddWorldPosition({ 3.0f,0.0f });
		}
		
		ChangeState(PlayerState::JUMP);
		NetForce.Y = 250.0f;
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
			ChangeState(PlayerState::IDLE);
		}
		else if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
		{
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
