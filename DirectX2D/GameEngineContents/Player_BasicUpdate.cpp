#include "PreCompile.h"
#include "Player.h"
#include "MapleMap.h"
#include "StatManager.h"
#include "FadeScreen.h"

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
	}
	else
	{
		RopePos = Transform.GetWorldPosition() + float4(0, -1);
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
			if (InputIsDown(VK_UP) && IsFadeIn == false)
			{
				ChangeState(PlayerState::PORTAL);
				std::string Level = Col->GetName();
				PrevLevelName = Level;

				std::list<std::shared_ptr<FadeScreen>> list = GetLevel()->GetObjectGroupConvert<FadeScreen>(ActorOrder::FadeScreen);
				std::list<std::shared_ptr<FadeScreen>>::iterator Start = list.begin();
				(*Start)->SettingAndStart(FadeType::FADEIN, Level);
				IsFadeIn = true;
			}
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{
			
		};
	Col->CollisionEvent(CollisionOrder::Portal, Event);
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
}