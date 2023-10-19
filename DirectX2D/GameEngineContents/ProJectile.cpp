#include "PreCompile.h"
#include "ProJectile.h"
#include "Player.h"
#include "SkillEffctor.h"
#include "StatManager.h"
ProJectile::ProJectile()
{
}

ProJectile::~ProJectile()
{
}

void ProJectile::Move(float _Delta)
{
	float4 Force = { Dir * Speed * _Delta, 0 };
	Transform.AddWorldPosition(Force);
}

void ProJectile::StartCoolTime(float _Delta)
{
	CoolTime -= _Delta;

	if (CoolTime <= 0)
	{
		GameEngineActor::Off();
	}
}

void ProJectile::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerWeapon);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 20,20 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer->CreateAnimation("Sureken", "Sureken", 0.1f, 0, 1, true);
		Renderer->SetSprite("Sureken");
		Renderer->ChangeAnimation("Sureken");
		Renderer->SetImageScale({ 20,20 });
		Renderer->SetRenderOrder(RenderOrder::Projectile);
		Renderer->AutoSpriteSizeOn();
	}

	GameEngineActor::Off();
}

void ProJectile::Update(float _Delta)
{
	if (Dir > 0)
	{
		Renderer->Transform.SetLocalScale({ -1,1 });
	}
	else if (Dir < 0)
	{
		Renderer->Transform.SetLocalScale({ 1,1 });
	}

	Move(_Delta);
	StartCoolTime(_Delta);
}

void ProJectile::StartFire()
{
	On();
}

void ProJectile::Off()
{
	if (SkillEffctor::Inst != nullptr)
	{
		SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::HitSureken, Dir);
	}
	
	GameEngineActor::Off();
}
