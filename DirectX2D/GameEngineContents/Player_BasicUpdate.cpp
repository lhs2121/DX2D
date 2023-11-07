#include "PreCompile.h"
#include "Player.h"
#include "MapleMap.h"
#include "StatManager.h"
#include "FadeScreen.h"
#include "ItemActor.h"

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
			if (CurState != PlayerState::FLASHJUMP)
			{
				NetForce.X = -125.0f;
			}
			if (Renderer->Transform.GetLocalScale().X < 0)
			{
				DetectedCol->Transform.SetLocalPosition({ -200.0f,33.0f });
				Renderer->Transform.SetLocalScale({ 1.0f,1.0f,1.0f });
				Dir = -1;
			}
		}
	}

	if (ApplyInputRight == true)
	{
		if (InputIsPress(VK_RIGHT))
		{
			if (CurState != PlayerState::FLASHJUMP)
			{
				NetForce.X = 125.0f;
			}
			if (Renderer->Transform.GetLocalScale().X > 0)
			{
				DetectedCol->Transform.SetLocalPosition({ 200.0f,33.0f });
				Renderer->Transform.SetLocalScale({ -1.0f,1.0f,1.0f });
				Dir = 1;
			}
		}
	}

	if (ApplyInputJump == true)
	{
		if (InputIsDown(JumpKey) && IsGrounded == true && CurState != PlayerState::DOWN)
		{
			NetForce.Y = 350.0f;
		}
		else if (InputIsDown(JumpKey) && CurState == PlayerState::DOWN)
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
	GameEngineColor Color = MapleMap::CurMap->GetColor(RopePos, GameEngineColor::MAGENTA);

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

				std::vector<std::shared_ptr<FadeScreen>> list = GetLevel()->GetObjectGroupConvert<FadeScreen>(ActorOrder::FadeScreen);
				list.front()->SettingAndStart(FadeType::FADEIN, Level);
				IsFadeIn = true;
			}
		};
	Event.Exit = [](GameEngineCollision*, GameEngineCollision* Col)
		{

		};
	Col->CollisionEvent(CollisionOrder::Portal, Event);
}

void Player::ItemCheck()
{
	Col->Collision(CollisionOrder::Item, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Col)
		{
			if (InputIsDown(PickUpKey))
			{
				_Col[0]->GetActor()->GetDynamic_Cast_This<ItemActor>()->AddItem();
			}
		});
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