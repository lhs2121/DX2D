#include "PreCompile.h"
#include "Player.h"
#include "SkillManager.h"
#include "Skill_ThorwSureken.h"

void Player::FlashJumpStart()
{
	NetForce.X = Dir * 700.0f;
	NetForce.Y += 100.0f;
	SkillManager::Inst->StartSkill(SkillType::FlashJump);
}

void Player::FlashJumpUpdate(float _Delta)
{
	if (IsGrounded == true && NetForce.Y <= 0)
	{
		ChangeState(PlayerState::IDLE);
	}

	if (CurColor == GameEngineColor::BLUE)
	{
		NetForce.X = Dir * 400.0f;
		NetForce.Y = 0;
		ChangeState(PlayerState::IDLE);
	}

	if (InputIsDown(JumpKey) && DoubleJump == false)
	{
		SkillManager::Inst->StartSkill(SkillType::FlashJump);
		NetForce.X = Dir * 700.0f;
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
	SkillManager::Inst->StartSkill(SkillType::QuadrupleThrow);
	ApplyInputJump = false;
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
		if (Dir < 0)
		{
			ApplyInputRight = false;
		}
		else if (Dir > 0)
		{
			ApplyInputLeft = false;
		}
	}

	if (Renderer->GetCurIndex() == 2)
	{
		
	}

	if (Renderer->IsCurAnimationEnd() == true)
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
	SkillManager::Inst->StartSkill(SkillType::ShowDown);
	ApplyInputJump = false;
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
		if (Dir < 0)
		{
			ApplyInputRight = false;
		}
		else if (Dir > 0)
		{
			ApplyInputLeft = false;
		}
	}

	if (Renderer->IsCurAnimationEnd())
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

void Player::BoosterStart()
{
	SkillManager::Inst->StartSkill(SkillType::SurekenBooster);
	ChangeState(PlayerState::WALK);
}

void Player::BoosterUpdate(float _Delta)
{
}

void Player::HasteStart()
{
	SkillManager::Inst->StartSkill(SkillType::Haste);
	ChangeState(PlayerState::WALK);
}

void Player::HasteUpdate(float _Delta)
{
}
