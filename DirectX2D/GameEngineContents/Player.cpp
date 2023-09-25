#include "PreCompile.h"
#include "Player.h"
#include "KCityMap.h"
#include "Monster.h"

Player::Player()
{
	CurState = PlayerState::IDLE;
	CurDirState = PlayerDirState::LEFT;
}

Player::~Player()
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		MainSpriteRenderer->SetSprite("idle");
	    //MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("Assets");
			Dir.MoveChild("Assets");
			Dir.MoveChild("Character");

			std::vector<GameEngineDirectory> DirGroup = Dir.GetAllDirectory();

			for (int i = 0; i < DirGroup.size(); i++)
			{
				std::string SpriteName = DirGroup[i].GetFileName();
				MainSpriteRenderer->CreateAnimation(SpriteName, SpriteName);
			}
		}

		MainSpriteRenderer->ChangeAnimation("idle");
		MainSpriteRenderer->SetRenderOrder(29);
	}

	{
		DebugRenderer0 = CreateComponent<GameEngineSpriteRenderer>(1);
		DebugRenderer0->SetRenderOrder(30);
		DebugRenderer0->SetSprite("etc");
		DebugRenderer0->Transform.SetLocalPosition(FootPos1);
	}

	{
		DebugRenderer1 = CreateComponent<GameEngineSpriteRenderer>(2);
		DebugRenderer1->SetRenderOrder(31);
		DebugRenderer1->SetSprite("etc", 1);
		DebugRenderer1->Transform.SetLocalPosition(FootPos2);
	}

	{
		DebugRenderer2 = CreateComponent<GameEngineSpriteRenderer>(3);
		DebugRenderer2->SetRenderOrder(31);
		DebugRenderer2->SetSprite("etc", 1);
		DebugRenderer2->Transform.SetLocalPosition(RopePos);
	}

	SetPos(FootPos1, FootPos2);
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	MainSpriteRenderer->SetPivotType(PivotType::Center);
	MainSpriteRenderer->AutoSpriteSizeOn();
	Transform.SetLocalPosition({ 500, -900, 0.0f });
}

void Player::Update(float _Delta)
{
	std::list<std::shared_ptr<Monster>> MonsterList =
		GetLevel()->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);

	for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	{
		CollisionData& Left = Transform.ColData;
		CollisionData& Right = MonsterPtr->Col->Transform.ColData;
 
		if (GameEngineTransform::Collision({Left , Right}))
		{
			MonsterPtr->Death();
		}
	}

	DirUpdate();
	CameraFocus();
	PhysicsActor::Update(_Delta);

	switch (CurState)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Delta);
		break;
	case PlayerState::RUN:
		RunUpdate(_Delta);
		break;
	case PlayerState::ROPE:
		RopeUpdate(_Delta);
		break;
	case PlayerState::DOWN:
		DownUpdate(_Delta);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Delta);
		break;
	default:
		break;
	}

	if (GameEngineInput::IsDown(VK_UP) && IsGrounded == true)
	{
		Jump();
	}
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
			FlipRenderer();;
		}
		ChangeDirState(PlayerDirState::RIGHT);
	}
}

void Player::CameraFocus()
{
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
}

void Player::FlipRenderer()
{
	MainSpriteRenderer->Transform.SetLocalScale({ -MainSpriteRenderer->Transform.GetLocalScale().X,1.0f,1.0f });
}




