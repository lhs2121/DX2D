#include "PreCompile.h"
#include "Player.h"
#include "KerningCityBG.h"

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
	if(IsJoin == true)
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
	
	if ((CalCulateColor(Transform.GetWorldPosition() + float4(0,-1)) != GameEngineColor::GREEN &&
		CalCulateColor(Transform.GetWorldPosition() + float4(0, 40 )) != GameEngineColor::GREEN))
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

void Player::AttackUpdate(float _Delta)
{
}