#include "PreCompile.h"
#include "Player.h"
#include "MapleMap.h"
#include "StatManager.h"

void Player::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	StateUpdate(_Delta);
	MoveUpdate();


	FlipRenderer();
	CameraFocus();
	DirUpdate();
	RopePivotUpdate();
	ColCheck();
	RopeCheck();
	PortalCheck();


	if (InputIsDown('P'))
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

	if (InputIsFree(VK_RIGHT) && InputIsPress(VK_LEFT))
	{
		ChangeDirState(PlayerDirState::LEFT);
		dir = -1;
	}
	else if (InputIsFree(VK_LEFT) && InputIsPress(VK_RIGHT))
	{
		ChangeDirState(PlayerDirState::RIGHT);
		dir = 1;
	}
}

void Player::RopePivotUpdate()
{
	if (InputIsPress(VK_UP))
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
	if (ApplyInput == false)
	{
		return;
	}

	if (ApplyInputLeft == true)
	{
		if (InputIsPress(VK_LEFT))
		{
			NetForce.X = -125.0f;
		}
	}

	if (ApplyInputRight == true)
	{
		if (InputIsPress(VK_RIGHT))
		{
			NetForce.X = 125.0f;
		}
	}

	if (ApplyInputJump == true)
	{
		if (InputIsDown(VK_MENU) && IsGrounded == true && CurState != PlayerState::DOWN)
		{
			NetForce.Y = 300.0f;
		}
		else if (InputIsDown(VK_MENU) && CurState == PlayerState::DOWN)
		{
			if (GetColor(Transform.GetWorldPosition() + float4(0, -5)) == GameEngineColor::RED)
			{
				return;
			}
			Transform.AddWorldPosition({ 0.0f,-5.0f });
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
			if (InputIsDown(VK_UP))
			{
				std::string Level = Col->GetName();
				PrevLevelName = Level;
				GameEngineCore::ChangeLevel(Level);
			}
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Col->CollisionEvent(CollisionOrder::Portal, Event);
}

void Player::ColCheck()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision*, GameEngineCollision* Col)
		{
			StatManager::Inst->ChangeHp(-10);
			StatManager::Inst->ChangeExp(10);
		};
	Event.Stay = [](GameEngineCollision*, GameEngineCollision* Col)
		{
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{
		
		};
	Col->CollisionEvent(CollisionOrder::Monster, Event);
}

void Player::CameraFocus()
{
	float4 Pos = Transform.GetWorldPosition();
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ Pos.X, Pos.Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}