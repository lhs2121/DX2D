#include "PreCompile.h"
#include "Player.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		MainSpriteRenderer->SetSprite("idle");

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
		DebugRenderer1->SetSprite("etc",1);
		DebugRenderer1->Transform.SetLocalPosition(FootPos2);
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	MainSpriteRenderer->SetPivotType(PivotType::Center);
	MainSpriteRenderer->AutoSpriteSizeOn();
	Transform.SetLocalPosition({ 500, -900, 0.0f });
}

void Player::Update(float _Delta)
{
	DirUpdate();
	GravityUpdate(_Delta);
	CameraFocus();

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
	case PlayerState::JUMP:
		JumpUpdate(_Delta);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Player::GravityUpdate(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition() + FootPos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		Transform.AddLocalPosition(GravityForce * _Delta);

		if (GravityForce.Y > -GlobalValue::MaxGravity)
		{
			GravityForce.Y -= 1000.0f * _Delta;
		}
	}
	//공중
	else if (GameEngineColor::RED == Color)
	{
		GravityForce.Y = 0;

		while (true)
		{
			float4 Pos2 = Transform.GetWorldPosition() + FootPos2;
			GameEngineColor Color2 = BackGround::MainMap->GetColor(Pos2, GameEngineColor::RED);

			if (GameEngineColor::RED != Color2)
			{
				break;
			}
			else if (GameEngineColor::RED == Color2)
			{
				Transform.AddLocalPosition(float4::UP);
			}
		}
	}
	//지면

	if (GameEngineColor::BLUE == Color)
	{
		while (true)
		{
			float4 Pos3 = Transform.GetWorldPosition() + FootPos2;
			GameEngineColor Color3 = BackGround::MainMap->GetColor(Pos3, GameEngineColor::RED);

			if (GameEngineColor::RED != Color3)
			{
				Transform.AddLocalPosition(float4::DOWN);
			}
			else if (GameEngineColor::RED == Color3)
			{
				break;
			}
		}
		while (true)
		{
			float4 Pos4 = Transform.GetWorldPosition() + FootPos2;
			GameEngineColor Color2 = BackGround::MainMap->GetColor(Pos4, GameEngineColor::RED);

			if (GameEngineColor::BLUE != Color2)
			{
				Transform.AddLocalPosition(float4::UP);
			}
			else if (GameEngineColor::BLUE == Color2)
			{
				break;
			}
		}
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




