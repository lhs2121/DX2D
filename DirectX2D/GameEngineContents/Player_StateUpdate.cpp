#include "PreCompile.h"
#include "Player.h"
#include "SurekenShooter.h"
#include "SkillManager.h"

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
	case PlayerState::HIT:
		HitUpdate(_Delta);
		break;
	case PlayerState::LUCKYSEVEN:
		LuckySevenUpdate(_Delta);
		break;
	case PlayerState::FLASHJUMP:
		FlashJumpUpdate(_Delta);
		break;
	case PlayerState::SHOWDOWN:
		ShowDownUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
{
	CurState = _State;
	CanFlip = true;
	DirCheck = true;
	ApplyInput = true;
	ApplyInputLeft = true;
	ApplyInputRight = true;
	ApplyInputJump = true;
	DoubleJump = false;

	switch (CurState)
	{
	case PlayerState::IDLE:
		Renderer->ChangeAnimation("idle");
		break;
	case PlayerState::WALK:
		Renderer->ChangeAnimation("walk");
		break;
	case PlayerState::JUMP:
		Renderer->ChangeAnimation("jump");
		break;
	case PlayerState::DOWN:
		CanFlip = false;
		ApplyInputLeft = false;
		ApplyInputRight = false;
		Renderer->ChangeAnimation("down");
		break;
	case PlayerState::ROPE:
		RopeStart();
		break;
	case PlayerState::HIT:
		HitStart();
		break;
	case PlayerState::PORTAL:
		PortalStart();
		break;
	case PlayerState::FLASHJUMP:
		FlashJumpStart();
		break;
	case PlayerState::LUCKYSEVEN:
		LuckySevenStart();
		break;
	case PlayerState::SHOWDOWN:
		ShowDownStart();
		break;
	default:
		break;
	}
}

void Player::RopeStart()
{
	ApplyInput = false;
	CanFlip = false;
	NetForce = 0.0f;

	if (IsGrounded == true && InputIsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0, -5 });
	}
	else if (IsGrounded == true && InputIsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, 5 });
	}

	Renderer->ChangeAnimation("rope");
	Renderer->AnimationPauseOn();
}

void Player::HitStart()
{

}

void Player::PortalStart()
{
	ApplyInput = false;
	CanFlip = false;
	Renderer->ChangeAnimation("idle");
}

void Player::IdleUpdate(float _Delta)
{
	if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::WALK);
	}
	if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	if (InputIsPress(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}
	if (InputIsPress(LuckySevenKey) && SurekenShooter::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
	if (InputIsPress(ShowDownKey))
	{
		ChangeState(PlayerState::SHOWDOWN);
	}
	if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
}

void Player::WalkUpdate(float _Delta)
{
	if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
	}
	if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
	//else if (InputIsPress(VK_DOWN) && CanRope == false)
	//{
	//	ChangeState(PlayerState::DOWN);
	//}
	if (InputIsPress(VK_DOWN) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	if (InputIsDown(LuckySevenKey) && SurekenShooter::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
	if (InputIsPress(ShowDownKey))
	{
		ChangeState(PlayerState::SHOWDOWN);
	}
}

void Player::JumpUpdate(float _Delta)
{
	if (NetForce.Y == 0 && IsGrounded == true)
	{
		if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
		{
			ChangeState(PlayerState::IDLE);
		}
		if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
		{
			ChangeState(PlayerState::WALK);
		}
	}

	if (InputIsDown(LuckySevenKey) && SurekenShooter::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
	else if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (InputIsDown(JumpKey) && InputIsPress(VK_DOWN) == false)
	{
		ChangeState(PlayerState::FLASHJUMP);
	}
	if (InputIsPress(ShowDownKey))
	{
		ChangeState(PlayerState::SHOWDOWN);
	}
}

void Player::RopeUpdate(float _Delta)
{
	float4 a = Transform.GetWorldPosition();
	NetForce = 0.0f;
	if (CurDirState == PlayerDirState::RIGHT)
	{
		ChangeDirState(PlayerDirState::LEFT);
		FlipRenderer();
	}

	Renderer->AnimationPauseOn();

	if (InputIsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, Speed * _Delta});
		Renderer->AnimationPauseOff();

		GameEngineColor TopColor = GetColor(Transform.GetWorldPosition() + float4(0, 65));
		GameEngineColor BottomColor = GetColor(Transform.GetWorldPosition() + float4(0, -1));

		if (TopColor != GameEngineColor::GREEN && BottomColor != GameEngineColor::GREEN)
		{
			ChangeState(PlayerState::IDLE);
			NetForce.Y = -100.0f;
			Renderer->AnimationPauseOff();
		}
	}
	else if (InputIsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0,-Speed * _Delta, 0 });
		Renderer->AnimationPauseOff();

		GameEngineColor TopColor = GetColor(Transform.GetWorldPosition() + float4(0, 65));
		GameEngineColor BottomColor = GetColor(Transform.GetWorldPosition() + float4(0, -1));

		if (BottomColor != GameEngineColor::GREEN)
		{
			ChangeState(PlayerState::IDLE);
			NetForce.Y = -100.0f;
			Renderer->AnimationPauseOff();
		}
	}

	if ((InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT)) && InputIsDown(JumpKey))
	{
		ChangeState(PlayerState::JUMP);
		NetForce.Y = 250.0f;
		Renderer->AnimationPauseOff();
	}
	if ((InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
		&& InputIsPress(VK_UP)
		&& InputIsDown(JumpKey))
	{
		if (InputIsPress(VK_LEFT))
		{
			Transform.AddWorldPosition({ -3.0f,0.0f });
		}
		else if (InputIsPress(VK_RIGHT))
		{
			Transform.AddWorldPosition({ 3.0f,0.0f });
		}

		ChangeState(PlayerState::JUMP);
		NetForce.Y = 250.0f;
		Renderer->AnimationPauseOff();
	}

}

void Player::DownUpdate(float _Delta)
{
	if (CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	if (InputIsFree(VK_DOWN))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (InputIsDown(VK_LEFT) || InputIsDown(VK_RIGHT))
	{
		ChangeState(PlayerState::WALK);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
}

void Player::HitUpdate(float _Delta)
{
	if (IsGrounded)
	{
		ChangeState(PlayerState::IDLE);
	}
}
