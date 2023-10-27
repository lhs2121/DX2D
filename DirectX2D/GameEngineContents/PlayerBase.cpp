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
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(ActorOrder::Manager);
	}

	{
		Stat = GetLevel()->CreateActor<StatDataPlayer>();
	}
}

void PlayerBase::Update(float _Delta)
{
	if (HitCoolTime > 0)
	{
		HitCoolTime -= _Delta;
	}
	if (HitCoolTime < 0)
	{
		Col->Collision(CollisionOrder::Monster, std::bind(&PlayerBase::HitByMonster, this, std::placeholders::_1));
	}

}

void PlayerBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel == nullptr)
	{
		return;
	}
	std::shared_ptr<PlayerBase> player = _PrevLevel->GetObjectGroupConvert<PlayerBase>(ActorOrder::Player).front();
	Stat = player->GetStat();
}

void PlayerBase::Release()
{
}

void PlayerBase::HitByMonster(std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
{
	float Damage = _Collision[0]->GetActor()->GetDynamic_Cast_This<MonsterBase>()->GetStat()->GetDamage();
	float ApplyDamage = Damage - Stat->DEF;
	Stat->CurHp -= ApplyDamage;
	HitCoolTime = 2.0f;
	DamageRenderer->RenderDamage(Transform.GetWorldPosition(), ApplyDamage, 1, DamageColor::Purple);

}
