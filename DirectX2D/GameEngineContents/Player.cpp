#include "PreCompile.h"
#include "Player.h"
#include "Portal.h"
#include "MapleLevel.h"

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
	//renderer
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
		MainSpriteRenderer->SetRenderOrder(RenderOrder::Player);
		MainSpriteRenderer->SetPivotValue({ 0.5f,0.71f });
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	{
		DebugRenderer0 = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer0->SetRenderOrder(RenderOrder::Debug);
		DebugRenderer0->SetSprite("etc");
		DebugRenderer0->Off();
	}

	{
		DebugRenderer1 = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer1->SetRenderOrder(RenderOrder::Debug);
		DebugRenderer1->SetSprite("etc", 1);
		DebugRenderer1->Transform.AddLocalPosition({ 0,1,0 });
		DebugRenderer1->Off();
	}

	{
		DebugRenderer2 = CreateComponent<GameEngineSpriteRenderer>(0);
		DebugRenderer2->SetRenderOrder(RenderOrder::Debug);
		DebugRenderer2->SetSprite("etc", 2);
		DebugRenderer2->Transform.AddLocalPosition({ 0,-1,0 });
		DebugRenderer2->Off();
	}

	//collision
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Player);
		Col->SetOrder(1);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 45,65 });
		Col->Transform.AddLocalPosition({ 0,35 });
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 500, -900, 0.0f });

	GameEngineInput::AddInputObject(this);
//	GetLevel()->GetMainCamera()->CameraTargetSetting(Transform, float4::BACKWARD * 500.0f);

	ChangeDirState(PlayerDirState::LEFT);
	ChangeState(PlayerState::IDLE);
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

void Player::Release()
{

}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel == nullptr)
	{
		return;
	}

	std::string name = _PrevLevel->GetName();
	MapleLevel* Level = GetLevel()->GetDynamic_Cast_This<MapleLevel>().get();
	std::shared_ptr<Portal> portal = Level->GetPortal(name);
	Transform.SetWorldPosition(portal->Transform.GetWorldPosition() + float4(0, -70));
}


