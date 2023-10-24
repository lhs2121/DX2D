#include "PreCompile.h"
#include "Player.h"
#include "BulletShooter.h"
#include "SkillEffctor.h"

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
		MainSpriteRenderer->ChangeAnimation("idle");
		break;
	case PlayerState::WALK:
		MainSpriteRenderer->ChangeAnimation("walk");
		break;
	case PlayerState::JUMP:
		MainSpriteRenderer->ChangeAnimation("jump");
		break;
	case PlayerState::DOWN:
		CanFlip = false;
		ApplyInputLeft = false;
		ApplyInputRight = false;
		MainSpriteRenderer->ChangeAnimation("down");
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
	default:
		break;
	}
}

void Player::MicroAdjustment()
{
	if (IsGrounded == true && InputIsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0, -5 });
	}
	else if (IsGrounded == true && InputIsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, 5 });
	}
}


void Player::RopeStart()
{
	ApplyInput = false;
	CanFlip = false;
	NetForce = 0.0f;
	MicroAdjustment();
	MainSpriteRenderer->ChangeAnimation("rope");
	MainSpriteRenderer->AnimationPauseOn();
}

void Player::FlashJumpStart()
{
	ApplyInputLeft = false;
	ApplyInputRight = false;
	NetForce.X = dir * 700.0f;
	NetForce.Y += 100.0f;
	SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::FlashJump, dir);
}

void Player::LuckySevenStart()
{
	ApplyInputJump = false;
	CanFlip = false;
	DirCheck = false;
	ChangeRandomSwingAnimation();
}

void Player::HitStart()
{

}

void Player::PortalStart()
{
	ApplyInput = false;
	CanFlip = false;
	MainSpriteRenderer->ChangeAnimation("idle");
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
	if (InputIsPress(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
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
	if (InputIsDown(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
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

	if (InputIsDown(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
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

	MainSpriteRenderer->AnimationPauseOn();

	if (InputIsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, Speed * _Delta});
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
	else if (InputIsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0,-Speed * _Delta, 0 });
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

	if ((InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT)) && InputIsDown(JumpKey))
	{
		ChangeState(PlayerState::JUMP);
		NetForce.Y = 250.0f;
		MainSpriteRenderer->AnimationPauseOff();
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
		MainSpriteRenderer->AnimationPauseOff();
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

void Player::LuckySevenUpdate(float _Delta)
{
	if (NetForce.Y == 0 && IsGrounded == true)
	{
		ApplyInputLeft = false;
		ApplyInputRight = false;
	}
	else
	{
		if (dir < 0)
		{
			ApplyInputRight = false;
		}
		else if (dir > 0)
		{
			ApplyInputLeft = false;
		}
	}

	if (MainSpriteRenderer->GetCurIndex() == 2 && BulletShooter::Inst->IsUpdate() == false)
	{
		BulletShooter::Inst->On();
		SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::LuckySeven, dir);
	}
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
		{
			ChangeState(PlayerState::IDLE);
		}
		else if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
		{
			ChangeState(PlayerState::WALK);
		}
	}
}

void Player::FlashJumpUpdate(float _Delta)
{
	if (IsGrounded == true && NetForce.Y <= 0)
	{
		ChangeState(PlayerState::IDLE);
	}

	if (CurColor == GameEngineColor::BLUE)
	{
		NetForce.X = dir * 400.0f;
		NetForce.Y = 0;
		ChangeState(PlayerState::IDLE);
	}

	if (InputIsDown(JumpKey) && DoubleJump == false)
	{
		SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::FlashJump, dir);
		NetForce.X = dir * 700.0f;
		NetForce.Y += 100.0f;
		DoubleJump = true;
	}
	if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
}

void Player::HitUpdate(float _Delta)
{
	if (IsGrounded)
	{
		ChangeState(PlayerState::IDLE);
	}

}

void Player::MeleeAttackUpdate(float _Delta)
{

}

void Player::AutoAttackUpdate(float _Delta)
{

}
