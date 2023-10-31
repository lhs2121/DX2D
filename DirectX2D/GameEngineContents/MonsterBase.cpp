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
	IdleAniName = MonsterName + "Idle";
	HitAniName = MonsterName + "Hit";
	DieAniName = MonsterName + "Die";

	Renderer->CreateAnimation(IdleAniName, IdleAniName, 0.2f);
	Renderer->CreateAnimation(HitAniName, HitAniName, 0.2f);
	Renderer->CreateAnimation(DieAniName, DieAniName, 0.3f);
	Renderer->ChangeAnimation(IdleAniName);

	ImageSize = Renderer->GetCurSprite().Texture->GetScale();
	Col->Transform.SetLocalScale(ImageSize);
	Col->Transform.AddLocalPosition({ 0,ImageSize.hY() });

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
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		Col->SetCollisionType(ColType::AABBBOX2D);
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
	if (Col != nullptr)
	{
		Col->Death();
		Col = nullptr;
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



