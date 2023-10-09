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
	CameraFocus();
	DirUpdate();
	ColCheck();
	RopePivotUpdate();
	RopeCheck();
	PortalCheck();
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('F'))
	{
		Speed += 50;
	}
	if (GameEngineInput::IsDown('G'))
	{
		ApplyForce = !ApplyForce;
	}
	if (GameEngineInput::IsDown(VK_MENU) && IsGrounded == true)
	{
		NetForce.Y = 300.0f;
	}
	if (CurDirState == PlayerDirState::LEFT)
	{
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			NetForce.X = -125.0f;
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			NetForce.X = 125.0f;
		}
	}
	else if (CurDirState == PlayerDirState::RIGHT)
	{
		if (GameEngineInput::IsPress(VK_RIGHT))
		{
			NetForce.X = 125.0f;
		}
		else if (GameEngineInput::IsPress(VK_LEFT))
		{
			NetForce.X = -125.0f;
		}
	}
}