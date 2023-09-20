#include "PreCompile.h"
#include "Player.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>

void Player::IdleUpdate(float _Delta)
{
	if (GravityForce.Y != 0)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("idle");
	}
	
	if (GameEngineInput::IsDown(VK_LEFT) || GameEngineInput::IsDown(VK_RIGHT))
	{
		ChangeState(PlayerState::RUN);
	}
}

void Player::RunUpdate(float _Delta)
{
	if (GravityForce.Y != 0)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("walk");
	}

	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::IDLE);
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
	MainSpriteRenderer->ChangeAnimation("rope");
}

void Player::DownUpdate(float _Delta)
{
	MainSpriteRenderer->ChangeAnimation("down");
}

void Player::AttackUpdate(float _Delta)
{
}