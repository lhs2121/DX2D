#include "PreCompile.h"
#include "Player.h"
#include "SurekenShooter.h"
#include "SkillEffctor.h"

void Player::FlashJumpStart()
{
	ApplyInputLeft = false;
	ApplyInputRight = false;
	NetForce.X = dir * 700.0f;
	NetForce.Y += 100.0f;
	SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::FlashJump, dir);
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

void Player::LuckySevenStart()
{
	ApplyInputJump = false;
	CanFlip = false;
	DirCheck = false;
	ChangeRandomSwingAnimation();
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

	if (MainSpriteRenderer->GetCurIndex() == 2 && SurekenShooter::Inst->IsUpdate() == false)
	{
		SurekenShooter::Inst->On();
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

void Player::ShowDownStart()
{
	ApplyInputJump = false;
	CanFlip = false;
	DirCheck = false;
	float4 SpawnPos = { Transform.GetWorldPosition().X + dir * 200.0f,Transform.GetWorldPosition().Y };
	SkillEffctor::Inst->StartEffect(SpawnPos, EffectType::ShowDown, dir);

	ChangeRandomSwingAnimation();
}

void Player::ShowDownUpdate(float _Delta)
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

	if (MainSpriteRenderer->IsCurAnimationEnd())
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
