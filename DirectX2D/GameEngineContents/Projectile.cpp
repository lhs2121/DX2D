#include "PreCompile.h"
#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Start()
{
	{
		SurekenRenderer = CreateComponent<GameEngineSpriteRenderer>();
		SurekenRenderer->SetRenderOrder(RenderOrder::Effect);
		SurekenRenderer->AutoSpriteSizeOn();
		SurekenRenderer->CreateAnimation("Sureken", "Sureken", 0.1f, 0, 1, true);
		SurekenRenderer->CreateAnimation("HitSureken", "HitSureken", 0.1f, 0, 3, false);
		SurekenRenderer->SetEndEvent("HitSureken",
			[&](GameEngineSpriteRenderer* _Renderer)
			{
				GameEngineActor::Off();
			});
		SurekenRenderer->ChangeAnimation("Sureken");
	}

	{
		SurekenCol = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerSkill);
		SurekenCol->SetCollisionType(ColType::AABBBOX2D);
		SurekenCol->Transform.SetLocalScale({ 20,20 });
	}
}

void Projectile::Update(float _Delta)
{
	if (SurekenRenderer->IsCurAnimation("Sureken"))
	{
		CoolTime -= _Delta;
		if (CoolTime <= 0.0f)
		{
			SurekenRenderer->ChangeAnimation("HitSureken");
		}

		float ForceX = Dir * Speed * _Delta;
		Transform.AddWorldPosition({ ForceX ,0 });
	}
}

void Projectile::Off()
{
	SurekenCol->Off();
	SurekenRenderer->ChangeAnimation("HitSureken");
}
