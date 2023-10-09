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
	CurState = PlayerState::IDLE;
	CurDirState = PlayerDirState::LEFT;
}

Player::~Player()
{
}

void Player::Start()
{
	{
		GetLevel()->CreateActor<LuckySeven>(9)->SetParent(this,7);
	}
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		
		MainSpriteRenderer->CreateAnimation("idle", "idle", 0.2f);
		MainSpriteRenderer->CreateAnimation("walk", "walk", 0.2f);
		MainSpriteRenderer->CreateAnimation("jump","jump");
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
		Col->Transform.AddLocalPosition({ 0,35});
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 500, -900, 0.0f });
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
		ApplyGravity = !ApplyGravity;
	}
	if (GameEngineInput::IsDown(VK_MENU) && IsGrounded == true)
	{
		Jump();
	}
	if (GravityForce.Y != 0 && CurState != PlayerState::ROPE)
	{
		MainSpriteRenderer->ChangeAnimation("jump");
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


void Player::DirUpdate()
{
	if ((GameEngineInput::IsFree(VK_RIGHT) && GameEngineInput::IsDown(VK_LEFT)) || (GameEngineInput::IsFree(VK_RIGHT) && GameEngineInput::IsPress(VK_LEFT)))
	{
		if (CurDirState == PlayerDirState::RIGHT)
		{
			FlipRenderer();
		}
		ChangeDirState(PlayerDirState::LEFT);
	}
	else if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsDown(VK_RIGHT) || (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsPress(VK_RIGHT)))
	{
		if (CurDirState == PlayerDirState::LEFT)
		{
			FlipRenderer();
		}
		ChangeDirState(PlayerDirState::RIGHT);
	}
}

void Player::RopePivotUpdate()
{
	if (GameEngineInput::IsPress(VK_DOWN))
	{
		RopePos = Transform.GetWorldPosition() + float4(0, -1);
		DebugRenderer2->Transform.SetLocalPosition({ 0,-1 });
	}
	else if(GameEngineInput::IsPress(VK_UP))
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
void Player::CameraFocus()
{
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}

void Player::FlipRenderer()
{
	if (CanFlip == false)
	{
		return;
	}

	if (CurDirState == PlayerDirState::LEFT)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ -1.0f,1.0f,1.0f });
	}
	if (CurDirState == PlayerDirState::RIGHT)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ 1.0f,1.0f,1.0f });
	}

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

	int CamOrder = static_cast<int>(ECAMERAORDER::Main);
	MainSpriteRenderer->SetViewCameraSelect(CamOrder);
	DebugRenderer0->SetViewCameraSelect(CamOrder);
	DebugRenderer1->SetViewCameraSelect(CamOrder);
	DebugRenderer2->SetViewCameraSelect(CamOrder);

	std::string name = _PrevLevel->GetName();
	std::shared_ptr<Portal> portal = GetMapleLevel()->GetPortal(name);
	Transform.SetWorldPosition(portal->Transform.GetWorldPosition() + float4(0,-70));
}


