#include "PreCompile.h"
#include "Player.h"
#include "MapleMap.h"

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

	if (GameEngineInput::IsDown('P'))
	{
		if (DebugRenderer0->IsUpdate())
		{
			DebugRenderer0->Off();
			DebugRenderer1->Off();
			DebugRenderer2->Off();
		}
		else
		{
			DebugRenderer0->On();
			DebugRenderer1->On();
			DebugRenderer2->On();
		}
	}
}

void Player::DirUpdate()
{
	if (DirCheck == false)
	{
		return;
	}

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
	if (ApplyForce == false)
	{
		return;
	}

	if (ApplyXForce == true)
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

	if (ApplyGForce == true)
	{
		if (GameEngineInput::IsDown(VK_MENU) && IsGrounded == true && CurState != PlayerState::DOWN)
		{
			NetForce.Y = 300.0f;
		}
		else if (GameEngineInput::IsDown(VK_MENU) && CurState == PlayerState::DOWN)
		{
			Transform.AddWorldPosition({ 0.0f,-3.0f });
		}
	}


}

void Player::RopeCheck()
{
	GameEngineColor Color = MapleMap::CurMap->GetColor(RopePos, GameEngineColor::ALAPA);

	if (GameEngineColor::GREEN == Color)
	{
		CanRope = true;
	}
	else
	{
		CanRope = false;
	}
}

void Player::PortalCheck()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Event.Stay = [&](GameEngineCollision*, GameEngineCollision* Col)
		{
			if (GameEngineInput::IsDown(VK_UP))
			{
				std::string Level = Col->GetName();
				PrevLevelName = Level;
				GameEngineCore::ChangeLevel(Level);
			}
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Col->CollisionEvent(CollisionType::Portal, Event);
}

void Player::ColCheck()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{
			Col->GetActor()->Death();
		};
	Col->CollisionEvent(CollisionType::Monster, Event);
}

void Player::CameraFocus()
{
	float4 Pos = Transform.GetWorldPosition();
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ Pos.X, Pos.Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}