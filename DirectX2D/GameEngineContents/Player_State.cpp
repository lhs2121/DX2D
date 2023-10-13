#include "PreCompile.h"
#include "Player.h"
#include "LuckySeven.h"
#include "EffectManager.h"

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

void Player::ChangeState(PlayerState _State)
{
	CurState = _State;
	CanFlip = true;
	DirCheck = true;
	ApplyForce = true;
	ApplyXForce = true;
	ApplyGForce = true;
	EffectManager = false;
	BrakingXForce = 1000.0f;


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
	if (IsGrounded == true && InputIsPress(VK_DOWN))
	{
		Transform.AddWorldPosition({ 0, -5 });
	}
	else if(IsGrounded == true && InputIsPress(VK_UP))
	{
		Transform.AddWorldPosition({ 0, 5 });
	}
}

void Player::IdleUpdate(float _Delta)
{
	if (InputIsPress(VK_LEFT) || InputIsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::WALK);
	}
	else if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (InputIsPress(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}
	else if (InputIsDown(LuckySevenKey) && LuckySeven::Inst->IsUpdate() == false)
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
	if (InputIsFree(VK_LEFT) && InputIsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (IsGrounded == false && NetForce.Y != 0)
	{
		ChangeState(PlayerState::JUMP);
	}
	//else if (InputIsPress(VK_DOWN) && CanRope == false)
	//{
	//	ChangeState(PlayerState::DOWN);
	//}
	else if (InputIsPress(VK_DOWN) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (InputIsDown(LuckySevenKey) && LuckySeven::Inst->IsUpdate() == false)
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

	if (InputIsDown(LuckySevenKey) && LuckySeven::Inst->IsUpdate() == false)
	{
		ChangeState(PlayerState::LUCKYSEVEN);
	}
	else if (InputIsPress(VK_UP) && CanRope == true)
	{
		ChangeState(PlayerState::ROPE);
	}
	else if (InputIsDown(JumpKey) && EffectManager == false)
	{
		ApplyXForce = false;
		EffectManager = true;

		BrakingXForce = 300.0f;
		NetForce.X = 600.0f;
		NetForce.Y += 100.0f;

		EffectManager::Inst->StartEffect(Transform.GetWorldPosition(), SkillType::FlashJump);
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

	if (InputIsPress(VK_UP))
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
	else if (InputIsPress(VK_DOWN))
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
		ApplyXForce = false;
	}

	if (MainSpriteRenderer->GetCurIndex() == 2)
	{
		LuckySeven::Inst->On();
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

void Player::MeleeAttackUpdate(float _Delta)
{
	
}

void Player::AutoAttackUpdate(float _Delta)
{
	
}
