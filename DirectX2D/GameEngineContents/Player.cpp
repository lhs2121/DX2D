#include "PreCompile.h"
#include "Player.h"
#include "Monster.h"
#include "MapleMap.h"
#include "Portal.h"
#include "MapleLevel.h"
#include "LuckySeven.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{
	{
		GetLevel()->CreateActor<LuckySeven>(9)->SetParent(this, 7);
	}
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);

		MainSpriteRenderer->CreateAnimation("idle", "idle", 0.2f);
		MainSpriteRenderer->CreateAnimation("walk", "walk", 0.2f);
		MainSpriteRenderer->CreateAnimation("jump", "jump");
		MainSpriteRenderer->CreateAnimation("down", "down");
		MainSpriteRenderer->CreateAnimation("rope", "rope", 0.2f);
		MainSpriteRenderer->CreateAnimation("ladder", "ladder", 0.2f);
		MainSpriteRenderer->CreateAnimation("swing1", "swing1", 0.2f, 0, 2, false);
		MainSpriteRenderer->CreateAnimation("swing2", "swing2", 0.2f, 0, 2, false);
		MainSpriteRenderer->CreateAnimation("swing3", "swing3", 0.2f, 0, 2, false);

		MainSpriteRenderer->ChangeAnimation("idle");
		MainSpriteRenderer->SetRenderOrder(0);
		MainSpriteRenderer->SetPivotValue({ 0.5,0.71 });
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	{
		DebugRenderer0 = CreateComponent<GameEngineSpriteRenderer>(1);
		DebugRenderer0->SetRenderOrder(1);
		DebugRenderer0->SetSprite("etc");
	}

	{
		DebugRenderer1 = CreateComponent<GameEngineSpriteRenderer>(2);
		DebugRenderer1->SetRenderOrder(1);
		DebugRenderer1->SetSprite("etc", 1);
		DebugRenderer1->Transform.AddLocalPosition({ 0,1,0 });
	}

	{
		DebugRenderer2 = CreateComponent<GameEngineSpriteRenderer>(3);
		DebugRenderer2->SetRenderOrder(1);
		DebugRenderer2->SetSprite("etc", 2);
		DebugRenderer2->Transform.AddLocalPosition({ 0,-1,0 });
	}

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 45,65 });
		Col->Transform.AddLocalPosition({ 0,35 });
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 500, -900, 0.0f });

	ChangeDirState(PlayerDirState::LEFT);
	ChangeState(PlayerState::IDLE);
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
	Col->CollisionEvent(ContentsCollisionType::Portal, Event);
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
	Col->CollisionEvent(ContentsCollisionType::Monster, Event);
}

void Player::CameraFocus()
{
	float4 Pos = Transform.GetWorldPosition();
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ Pos.X, Pos.Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}

void Player::FlipRenderer()
{
	if (CanFlip == false)
	{
		return;
	}

	float4 Scale = MainSpriteRenderer->Transform.GetLocalScale();

	if (Scale.X == 1 && NetForce.X > 0)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ -1.0f,1.0f,1.0f });
	}
	if (Scale.X == -1 && NetForce.X < 0)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ 1.0f,1.0f,1.0f });
	}

}

void Player::ChangeRandomSwingAnimation()
{
	int RandomNumber = GameEngineRandom::GameEngineRandom().RandomInt(1, 3);
	std::string AnimationName = "swing" + std::to_string(RandomNumber);
	MainSpriteRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (false == _NextLevel->GetDynamic_Cast_This<MapleLevel>()->FindActor(1))
	{
		SetParent(_NextLevel, 1);
	}
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel == nullptr)
	{
		return;
	}
	_PrevLevel->GetDynamic_Cast_This<MapleLevel>()->EraseActor();

	int MainCamOrder = static_cast<int>(ECAMERAORDER::Main);
	MainSpriteRenderer->SetViewCameraSelect(MainCamOrder);
	DebugRenderer0->SetViewCameraSelect(MainCamOrder);
	DebugRenderer1->SetViewCameraSelect(MainCamOrder);
	DebugRenderer2->SetViewCameraSelect(MainCamOrder);

	std::string name = _PrevLevel->GetName();
	std::shared_ptr<Portal> portal = GetMapleLevel()->GetPortal(name);
	Transform.SetWorldPosition(portal->Transform.GetWorldPosition() + float4(0, -70));
}


