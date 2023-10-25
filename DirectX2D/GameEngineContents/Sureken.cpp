#include "PreCompile.h"
#include "Sureken.h"
#include "Player.h"
#include "SkillEffctor.h"
#include "StatManager.h"
Sureken::Sureken()
{
}

Sureken::~Sureken()
{
}

void Sureken::Move(float _Delta)
{
	float4 Force = { Dir * Speed * _Delta, 0 };
	Transform.AddWorldPosition(Force);
}

void Sureken::StartCoolTime(float _Delta)
{
	CoolTime -= _Delta;

	if (CoolTime <= 0)
	{
		GameEngineActor::Off();
	}
}

void Sureken::Start()
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
		Renderer->SetRenderOrder(RenderOrder::Sureken);
		Renderer->AutoSpriteSizeOn();
	}

	GameEngineActor::Off();
}

void Sureken::Update(float _Delta)
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

void Sureken::StartFire()
{
	On();
}

void Sureken::Off()
{
	if (SkillEffctor::Inst != nullptr)
	{
		SkillEffctor::Inst->StartEffect(Transform.GetWorldPosition(), EffectType::HitSureken, Dir);
	}
	
	GameEngineActor::Off();
}
