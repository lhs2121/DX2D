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
	MainSpriteRenderer->ChangeAnimation("idle");
}

void Player::RunUpdate(float _Delta)
{
	MainSpriteRenderer->ChangeAnimation("walk");

	DirUpdate();

	if (GameEngineInput::IsPress(VK_UP))
	{
		Transform.AddLocalPosition({ 0, speed * _Delta, 0 });
	}
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		float4 LeftPos = Transform.GetWorldPosition() + float4(-43, 0);
		GameEngineColor Color = BackGround::MainMap->GetColor(LeftPos, GameEngineColor::RED);

		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ -speed * _Delta, 0, 0 });
		}
	}
	if (GameEngineInput::IsPress(VK_DOWN))
	{
		float4 BottomPos = Transform.GetWorldPosition() + float4(0, -43);
		GameEngineColor Color = BackGround::MainMap->GetColor(BottomPos, GameEngineColor::RED);

		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ 0, -speed * _Delta, 0 });
		}
	}
	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		float4 RightPos = Transform.GetWorldPosition() + float4(43, 0);
		GameEngineColor Color = BackGround::MainMap->GetColor(RightPos, GameEngineColor::RED);

		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ speed * _Delta, 0, 0 });
		}
		
	}
}

void Player::RopeUpdate(float _Delta)
{
}

void Player::DownUpdate(float _Delta)
{
}

void Player::JumpUpdate(float _Delta)
{
}