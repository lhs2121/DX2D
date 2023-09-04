#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("Run", "HoHoYee_AttackABC", 0.05f, -1, -1, true);
		MainSpriteRenderer->ChangeAnimation("Run");
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

		MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));

		// MainSpriteRenderer->Transform.SetLocalScale({5, 5});
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(2.0f);
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	//if (xxxx ��Ȳ�� �Ǹ�)
	//{
	//	MainSpriteRenderer->Death();
	//	MainSpriteRenderer = nullptr;
	//}

	// �浹�߳� ���߳ĸ� ����

	//std::list<std::shared_ptr<Monster>> MonsterList = 
	//	GetLevel()->GetObjectGroup<Monster>(ContentsType::Monster);

	//for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	//{
	//	if (Renderer->Transform.Collision(MonsterPtr->Renderer->Transform))
	//	{
	//		// �浹�ߴ�.
	//	}
	//}


	float Speed = 100.0f;

	if (GameEngineInput::IsDown('A'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}


	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GrivityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	else 
	{
		GrivityForce = 0.0f;
	}
	// ���� ���ٰ��ϰ� �ʹٸ� while������ �÷��ּ���.


	// float4 Color = GetColor(Transform.GetWorldPosition());
}