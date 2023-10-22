#include "PreCompile.h"
#include "Player.h"
#include "MapleMap.h"
#include "StatManager.h"

void Player::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	FlipRenderer();
	CameraFocus();
	DirUpdate();
	RopePivotUpdate();
	ColCheck(_Delta);
	RopeCheck();
	PortalCheck();
	MoveUpdate();
	StateUpdate(_Delta);

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
		if (InputIsDown(VK_MENU) && IsGrounded == true && CurState != StatDatae::DOWN)
		{
			NetForce.Y = 300.0f;
		}
		else if (InputIsDown(VK_MENU) && CurState == StatDatae::DOWN)
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

void Player::ColCheck(float _Delta)
{
	if (CanHit == false)
	{
		HitCoolTime -= _Delta;

		if (HitCoolTime <= 0)
		{
			CanHit = true;
			HitCoolTime = 2.0f;
		}
		return;
	}

	EventParameter Event;

	Event.Enter = [&](GameEngineCollision*, GameEngineCollision* Col)
		{
			StatManager::Inst->ChangeHp(PlayerStat.get(), -50.0f);
			CanHit = false;
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
	float4 PlayerPos = Transform.GetWorldPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	if (PlayerPos.X - ContentsCore::GetStartWindowSize().hX() > 0 && PlayerPos.X + ContentsCore::GetStartWindowSize().hX() < MapleMap::CurMap->GetMapScale().X)
	{
		CameraPos.X = PlayerPos.X;
	}
	if (PlayerPos.Y - ContentsCore::GetStartWindowSize().hY() > -MapleMap::CurMap->GetMapScale().Y)
	{
		CameraPos.Y = PlayerPos.Y;
	}

	GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ CameraPos.X ,CameraPos.Y,CameraPos.Z });

	if (CameraPos.X - ContentsCore::GetStartWindowSize().hX() < 0)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::RIGHT * 100.0f);
			float X = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X - ContentsCore::GetStartWindowSize().hX();
			if (X >= 0)
			{
				break;
			}
		}
	}
	if (CameraPos.X + ContentsCore::GetStartWindowSize().hX() > MapleMap::CurMap->GetMapScale().X)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::LEFT * 100.0f);
			float X = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X + ContentsCore::GetStartWindowSize().hX();
			if (X <= MapleMap::CurMap->GetMapScale().X)
			{
				break;
			}
		}
	}
	if (CameraPos.Y - ContentsCore::GetStartWindowSize().hY() < -MapleMap::CurMap->GetMapScale().Y)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::UP * 100.0f);
			float Y = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y - ContentsCore::GetStartWindowSize().hY();
			if (Y >= -MapleMap::CurMap->GetMapScale().Y)
			{
				break;
			}
		}
	}
}