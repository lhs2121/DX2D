#include "PreCompile.h"
#include "PlayerBase.h"
#include "DamageIndicator.h"
#include "StatData.h"
#include "MonsterBase.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->CreateAnimation("idle", "idle", 0.2f);
		Renderer->CreateAnimation("walk", "walk", 0.2f);
		Renderer->CreateAnimation("jump", "jump");
		Renderer->CreateAnimation("down", "down");
		Renderer->CreateAnimation("rope", "rope", 0.2f);
		Renderer->CreateAnimation("ladder", "ladder", 0.2f);
		Renderer->CreateAnimation("hit", "hit", 0.3f);
		Renderer->CreateAnimation("swing1", "swing1", 0.2f, 0, 2, false);
		Renderer->CreateAnimation("swing2", "swing2", 0.2f, 0, 2, false);
		Renderer->CreateAnimation("swing3", "swing3", 0.2f, 0, 2, false);
		Renderer->ChangeAnimation("idle");
		Renderer->SetRenderOrder(RenderOrder::Player);
		Renderer->SetPivotValue({ 0.5f,0.71f });
		Renderer->AutoSpriteSizeOn();
	}

	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Player);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 45,65 });
		Col->Transform.AddLocalPosition({ 0,33 });
	}
	{
		DetectedCol = CreateComponent<GameEngineCollision>(99);
		DetectedCol->SetCollisionType(ColType::AABBBOX2D);
		DetectedCol->Transform.SetLocalScale({ 400,100 });
		DetectedCol->Transform.AddLocalPosition({ 0,33 });
	}
	{
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(ActorOrder::Manager);
	}

	{
		Stat = GetLevel()->CreateActor<StatDataPlayer>();
	}
}

void PlayerBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel == nullptr)
	{
		return;
	}
	// Ω∫≈» ¿Ã¿¸
	std::shared_ptr<PlayerBase> PrevPlayer = _PrevLevel->GetObjectGroupConvert<PlayerBase>(ActorOrder::Player).front();
	Stat = PrevPlayer->GetStat();
}

void PlayerBase::Release()
{
}


