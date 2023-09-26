#include "PreCompile.h"
#include "Player.h"
#include "KCityMap.h"

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::RUN);
	}
	else if (GameEngineInput::IsDown(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}

	if (GravityForce.Y != 0)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("idle");
	}
}

void Player::RunUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
	}
	else if (GameEngineInput::IsDown(VK_DOWN) && IsGrounded == true)
	{
		ChangeState(PlayerState::DOWN);
	}

	if (GravityForce.Y != 0)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("walk");
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
	//if (GameEngineInput::IsPress(VK_DOWN))
	//{
	//	Transform.AddLocalPosition({ 0, -Speed * _Delta, 0 });
	//}
	//else if (GameEngineInput::IsPress(VK_UP))
	//{
	//	Transform.AddLocalPosition({ 0, Speed * _Delta, 0 });
	//}
}

void Player::RopeUpdate(float _Delta)
{
	MainSpriteRenderer->ChangeAnimation("rope");

	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition({ 0, Speed * _Delta, 0 });
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		Transform.AddLocalPosition({ 0,-Speed * _Delta, 0 });
	}
}

void Player::DownUpdate(float _Delta)
{
	if (CanClimbRope == true)
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

	if (GravityForce.Y != 0)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("down");
	}
}

void Player::AttackUpdate(float _Delta)
{
}