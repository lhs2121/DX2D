#include "PreCompile.h"
#include "Player.h"

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
void Player::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	FlipRenderer();
	CameraFocus();
	DirUpdate();
	RopePivotUpdate();
	ColCheck();
	RopeCheck();
	PortalCheck();
	StateUpdate(_Delta);
	MoveUpdate();
}

void Player::DirUpdate()
{
	if (GameEngineInput::IsFree(VK_RIGHT) && GameEngineInput::IsPress(VK_LEFT))
	{
		ChangeDirState(PlayerDirState::LEFT);
	}
	else if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeDirState(PlayerDirState::RIGHT);
	}
}

void Player::RopePivotUpdate()
{
	if (GameEngineInput::IsPress(VK_UP))
	{
		RopePos = Transform.GetWorldPosition() + float4(0, 65);
		DebugRenderer2->Transform.SetLocalPosition({ 0,65 });
	}
	else
	{
		RopePos = Transform.GetWorldPosition() + float4(0, -1);
		DebugRenderer2->Transform.SetLocalPosition({ 0,-1 });
	}
}

void Player::MoveUpdate()
{
	if (GameEngineInput::IsDown(VK_MENU) && IsGrounded == true && CurState != PlayerState::DOWN)
	{
		NetForce.Y = 300.0f;
	}
	else if (GameEngineInput::IsDown(VK_MENU) && CurState == PlayerState::DOWN)
	{
		Transform.AddWorldPosition({ 0.0f,-3.0f });
	}
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		NetForce.X = -125.0f;
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		NetForce.X = 125.0f;
	}
}
