#include "PreCompile.h"
#include "Sureken.h"
#include "Player.h"
#include "SkillEffctor.h"
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
	std::shared_ptr<StatData> playerstat = Player::MainPlayer->GetDynamic_Cast_This<CombatActor>()->GetStatData();
	SetDamage(playerstat->GetDamage());
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
