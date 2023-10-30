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

void Projectile::Setting(float4 _Pos, float _Speed, float _Dir, float _CoolTime, float _StartDelayTime)
{
	float4 Offset = { _Dir * 20.0f,33.0f };
	Transform.SetWorldPosition(_Pos + Offset);
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
		SurekenRenderer->CreateAnimation("Sureken", "Sureken", 0.1f, 0, 1, true);
		SurekenRenderer->AutoSpriteSizeOn();

	}

	{
		SurekenCol = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerSkill);
		SurekenCol->SetCollisionType(ColType::AABBBOX2D);
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

		CoolTime -= _Delta;
		if (CoolTime <= 0.0f)
		{
			GameEngineActor::Off();
		}

		float ForceX = Dir * Speed * _Delta;
		Transform.AddWorldPosition({ ForceX ,0 });
	}

	SurekenCol->Collision(CollisionOrder::Monster,
		[&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
		{
			if (CanHitMonster == false)
			{
				return;
			}
			CanHitMonster = false;
			_Collision[0]->GetActor()->GetDynamic_Cast_This<Monster>()->PushDamage(DamageGroup,DamageID);
			SurekenRenderer->ChangeAnimation("Hit_LuckySeven");
		});
}

void Projectile::On()
{
	SurekenCol->Off();
	SurekenRenderer->Off();
	GameEngineActor::On();
}

