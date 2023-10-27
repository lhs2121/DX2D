#include "PreCompile.h"
#include "MonsterBase.h"
#include "DamageIndicator.h"
#include "DamageActor.h"
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

void MonsterBase::Update(float _Delta)
{
	if (HitCoolTime > 0)
	{
		HitCoolTime -= _Delta;
	}
	if (HitCoolTime < 0)
	{
		Col->Collision(CollisionOrder::PlayerSkill, std::bind(&MonsterBase::HitByPlayer, this, std::placeholders::_1));
	}
}

void MonsterBase::Release()
{

}

void MonsterBase::HitByPlayer(std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
{
	for (size_t i = 0; i < _Collision.size(); i++)
	{
		std::shared_ptr<DamageActor> DmgActor = _Collision[i]->GetActor()->GetDynamic_Cast_This<DamageActor>();
		float Damage = DmgActor->GetDamage();
		Hp -= Damage;
		DamageRenderer->RenderDamage(Transform.GetWorldPosition(), Damage, 5, DamageColor::Orange);

		DmgActor->Off();
	}
}

