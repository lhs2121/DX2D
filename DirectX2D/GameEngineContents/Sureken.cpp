#include "PreCompile.h"
#include "Sureken.h"
#include "Player.h"
#include "SkillManager.h"
#include "StatManager.h"
#include "StatData.h"

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
	DamageActor::Start();
	SetCollisionScale({ 20,20 });
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
	DamageActor::Update(_Delta);
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
	SetDamage(15.0f);
	DamageActor::On();
	On();
}

void Sureken::Off()
{
	if (SkillManager::Inst != nullptr)
	{
		SkillManager::Inst->StartSkill(Transform.GetWorldPosition(), SkillType::HitSureken, Dir);
	}
	
	GameEngineActor::Off();
}
