#include "PreCompile.h"
#include "Player.h"
#include "BulletShooter.h"
#include "SkillEffctor.h"

void Player::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case StatDatae::IDLE:
		IdleUpdate(_Delta);
		break;
	case StatDatae::WALK:
		WalkUpdate(_Delta);
		break;
	case StatDatae::JUMP:
		JumpUpdate(_Delta);
		break;
	case StatDatae::ROPE:
		RopeUpdate(_Delta);
		break;
	case StatDatae::DOWN:
		DownUpdate(_Delta);
		break;
	case StatDatae::HIT:
		HitUpdate(_Delta);
		break;
	case StatDatae::LUCKYSEVEN:
		LuckySevenUpdate(_Delta);
		break;
	case StatDatae::FLASHJUMP:
		FlashJumpUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Player::ChangeState(StatDatae _State)
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
	case StatDatae::IDLE:
		MainSpriteRenderer->ChangeAnimation("idle");
		break;
	case StatDatae::WALK:
		MainSpriteRenderer->ChangeAnimation("walk");
		break;
	case StatDatae::JUMP:
		MainSpriteRenderer->ChangeAnimation("jump");
		break;
	case StatDatae::DOWN:
		CanFlip = false;
		ApplyInputLeft = false;
		ApplyInputRight = false;
		MainSpriteRenderer->ChangeAnimation("down");
		break;
	case StatDatae::ROPE:
		RopeStart();
		break;
	case StatDatae::HIT:
		HitStart();
		break;
	case StatDatae::FLASHJUMP:
		FlashJumpStart();
		break;
	case StatDatae::LUCKYSEVEN:
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

void Player::IdleUpdate(float _Delta)
{
	if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
	{
		ChangeState(StatDatae::WALK);
	}
	if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(StatDatae::ROPE);
	}
	if (InputIsPress(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(StatDatae::DOWN);
	}
	if (InputIsPress(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
	{
		ChangeState(StatDatae::LUCKYSEVEN);
	}
	if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(StatDatae::JUMP);
	}
}

void Player::WalkUpdate(float _Delta)
{
	if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
	{
		ChangeState(StatDatae::IDLE);
	}
	if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(StatDatae::JUMP);
	}
	//else if (InputIsPress(VK_DOWN) && CanRope == false)
	//{
	//	ChangeState(StatDatae::DOWN);
	//}
	if (InputIsPress(VK_DOWN) && CanRope == true)
	{
		ChangeState(StatDatae::ROPE);
	}
	if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(StatDatae::ROPE);
	}
	if (InputIsDown(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
	{
		ChangeState(StatDatae::LUCKYSEVEN);
	}
}

void Player::JumpUpdate(float _Delta)
{
	if (NetForce.Y == 0 && IsGrounded == true)
	{
		if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
		{
			ChangeState(StatDatae::IDLE);
		}
		if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
		{
			ChangeState(StatDatae::WALK);
		}
	}

	if (InputIsDown(LuckySevenKey) && BulletShooter::Inst->IsUpdate() == false)
	{
		ChangeState(StatDatae::LUCKYSEVEN);
	}
	else if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(StatDatae::ROPE);
	}
	else if (InputIsDown(JumpKey) && InputIsPress(VK_DOWN) == false)
	{
		ChangeState(StatDatae::FLASHJUMP);
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
			ChangeState(StatDatae::IDLE);
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
			ChangeState(StatDatae::IDLE);
			NetForce.Y = -100.0f;
			MainSpriteRenderer->AnimationPauseOff();
		}
	}

	if ((InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT)) && InputIsDown(JumpKey))
	{
		ChangeState(StatDatae::JUMP);
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

		ChangeState(StatDatae::JUMP);
		NetForce.Y = 250.0f;
		MainSpriteRenderer->AnimationPauseOff();
	}

}

void Player::DownUpdate(float _Delta)
{
	if (CanRope == true)
	{
		ChangeState(StatDatae::ROPE);
	}
	if (InputIsFree(VK_DOWN))
	{
		ChangeState(StatDatae::IDLE);
	}
	else if (InputIsDown(VK_LEFT) || InputIsDown(VK_RIGHT))
	{
		ChangeState(StatDatae::WALK);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(StatDatae::JUMP);
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
			ChangeState(StatDatae::IDLE);
		}
		else if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
		{
			ChangeState(StatDatae::WALK);
		}
	}
}

void Player::FlashJumpUpdate(float _Delta)
{
	if (IsGrounded == true && NetForce.Y <= 0)
	{
		ChangeState(StatDatae::IDLE);
	}

	if (CurColor == GameEngineColor::BLUE)
	{
		NetForce.X = dir * 400.0f;
		NetForce.Y = 0;
		ChangeState(StatDatae::IDLE);
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
		ChangeState(StatDatae::ROPE);
	}
}

void Player::HitUpdate(float _Delta)
{
	if (IsGrounded)
	{
		ChangeState(StatDatae::IDLE);
	}

}

void Player::MeleeAttackUpdate(float _Delta)
{

}

void Player::AutoAttackUpdate(float _Delta)
{

}
