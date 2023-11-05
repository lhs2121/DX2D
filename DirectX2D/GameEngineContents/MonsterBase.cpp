#include "PreCompile.h"
#include "MonsterBase.h"
#include "DamageIndicator.h"
#include "StatData.h"

MonsterBase::MonsterBase()
{
}

MonsterBase::~MonsterBase()
{
}

void MonsterBase::Setting(std::string MonsterName)
{
	IdleAniName = MonsterName + "_Idle";
	HitAniName = MonsterName + "_Hit";
	DieAniName = MonsterName + "_Die";
	ItemName = MonsterName + "_Item";

	Renderer->CreateAnimation(IdleAniName, IdleAniName, 0.2f);
	Renderer->CreateAnimation(HitAniName, HitAniName, 0.2f);
	Renderer->CreateAnimation(DieAniName, DieAniName, 0.3f);
	Renderer->ChangeAnimation(IdleAniName);

	ImageSize = Renderer->GetCurSprite().Texture->GetScale();
	HitCol->Transform.SetLocalScale(ImageSize);
	HitCol->Transform.AddLocalPosition({ 0,ImageSize.hY() });
	AttackCol->Transform.SetLocalScale(ImageSize);
	AttackCol->Transform.AddLocalPosition({ 0,ImageSize.hY() });

	On();
}

void MonsterBase::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->SetPivotType(PivotType::Bottom);
		Renderer->AutoSpriteSizeOn();
	}

	{
		HitCol = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		HitCol->SetCollisionType(ColType::AABBBOX2D);

		AttackCol = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
	}

	{
		DamageRenderer = GetLevel()->CreateActor<DamageIndicator>(ActorOrder::Manager);
	}

	{
		Stat = GetLevel()->CreateActor<StatDataMonster>();
	}
	Off();
}

void MonsterBase::Release()
{
	if (Renderer != nullptr)
	{
		Renderer->Death();
		Renderer = nullptr;
	}
	if (HitCol != nullptr)
	{
		HitCol->Death();
		HitCol = nullptr;
	}
	if (AttackCol != nullptr)
	{
		AttackCol->Death();
		AttackCol = nullptr;
	}
	if (DamageRenderer != nullptr)
	{
		DamageRenderer->Death();
		DamageRenderer = nullptr;
	}
	if (Stat != nullptr)
	{
		Stat->Death();
		Stat = nullptr;
	}
}



