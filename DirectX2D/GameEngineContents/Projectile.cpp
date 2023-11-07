#include "PreCompile.h"
#include "Projectile.h"
#include "Monster.h"
#include "StatData.h"


Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Setting(float4 _Pos, float _Speed, float4 _Dir, float _CoolTime, float _StartDelayTime)
{
	Transform.SetWorldPosition(_Pos);
	Speed = _Speed;
	Dir = _Dir;
	CoolTime = _CoolTime;
	CoolTimeReset = _CoolTime;
	StartDelayTime = _StartDelayTime;
	CanHitMonster = true;

	if (_Dir == 1)
	{
		Transform.SetLocalScale({ -1,1 });
	}
	else if (_Dir == -1)
	{
		Transform.SetLocalScale({ 1,1 });
	}

	SurekenRenderer->ChangeAnimation("Sureken");

	On();
}

void Projectile::SetDamage(std::vector<float> _DamageGroup, int _DamageID)
{
	DamageGroup = _DamageGroup;
	DamageID = _DamageID;
}

void Projectile::Start()
{
	{
		SurekenRenderer = CreateComponent<GameEngineSpriteRenderer>();
		SurekenRenderer->SetRenderOrder(RenderOrder::Effect);
		SurekenRenderer->CreateAnimation("Hit_LuckySeven", "Hit_LuckySeven");
		SurekenRenderer->SetEndEvent("Hit_LuckySeven",
			[&](GameEngineSpriteRenderer* _Renderer)
			{
				Off();
			});
		SurekenRenderer->CreateAnimation("Sureken", "Sureken", 0.1f, 2, 3, true);
		SurekenRenderer->AutoSpriteSizeOn();

	}

	{
		SurekenCol = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
		SurekenCol->SetCollisionType(ColType::SPHERE2D);
		SurekenCol->Transform.SetLocalScale({ 20,20 });
	}

	Off();
}

void Projectile::Update(float _Delta)
{
	if (StartDelayTime > 0.0f)
	{
		StartDelayTime -= _Delta;
		return;
	}

	SurekenRenderer->On();
	SurekenCol->On();

	if (SurekenRenderer->IsCurAnimation("Sureken"))
	{
		if (Target != nullptr)
		{
			float4 TargetPos = Target->Transform.GetWorldPosition() + float4(0.0f, HitPosOffset.Y);
			float4 TargetDir = TargetPos - Transform.GetWorldPosition();
			if (TargetDir.ToABS().X <= 20.0f)
			{
				if (Target->IsDeath() == false)
				{
					Target->RenderDamage(DamageGroup, DamageID);
				}
				else
				{
					Off();
				}
				SurekenRenderer->ChangeAnimation("Hit_LuckySeven");
				Target = nullptr;
			}

			TargetDir.Normalize();
			Transform.AddWorldPosition(TargetDir * Speed * _Delta);
		}
		else
		{
			CoolTime -= _Delta;
			if (CoolTime <= 0.0f)
			{
				Off();
			}

			Transform.AddWorldPosition(Dir * Speed * _Delta);
		}
	}
}

void Projectile::On()
{
	SurekenCol->Off();
	SurekenRenderer->Off();
	GameEngineActor::On();
}

