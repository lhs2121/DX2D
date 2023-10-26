#include "PreCompile.h"
#include "SkillEffect.h"
#include "Player.h"
#include "DamageActor.h"

SkillEffect::SkillEffect()
{
}

SkillEffect::~SkillEffect()
{
}

void SkillEffect::FlipX(int _dir)
{
	if (_dir == 1)
	{
		Renderer->Transform.SetLocalScale({ -1,1 });
	}
	else if (_dir == -1)
	{
		Renderer->Transform.SetLocalScale({ 1,1 });
	}
	
}

void SkillEffect::EffectSetting(float4 _Pos, SkillType _Type, float _Dir)
{
	int random = GameEngineRandom::GameEngineRandom().RandomInt(1, 30);

	float4 OffSet;

	switch (_Type)
	{
	case SkillType::FlashJump:
		OffSet = { _Dir * -15.0f,10.0f };
		Renderer->ChangeAnimation("FlashJump");
		break;
	case SkillType::LuckySeven:
		_Dir = Player::MainPlayer->GetDir();
		OffSet = { _Dir * 40.0f,30.0f };
		Renderer->ChangeAnimation("LuckySeven");
		break;
	case SkillType::HitSureken:
		OffSet = { _Dir * random,0.0f };
		Renderer->ChangeAnimation("HitSureken");
		break;
	case SkillType::ShowDown:
		OffSet = { _Dir * 100.0f,50.0f };
		Renderer->ChangeAnimation("ShowDownChallenge");
		Renderer->SetFrameEvent("ShowDownChallenge", 8, 
			[&](GameEngineSpriteRenderer* Renderer)
			{
				std::shared_ptr<DamageActor> Dmg = GetLevel()->CreateActor<DamageActor>();
				SkillDamage = Dmg;
				Dmg->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition() + float4(250 * Player::MainPlayer->GetDir(),0));
				Dmg->SetCollisionScale({ 400,300 });
				Dmg->SetDamage(Player::MainPlayer->GetDamage());
				Dmg->On();
			});
		Renderer->SetFrameEvent("ShowDownChallenge", 12,
			[&](GameEngineSpriteRenderer* Renderer)
			{
				SkillDamage->Off();
			});
		break;
	default:
		break;
	}

	Transform.SetWorldPosition(_Pos + OffSet);
	Renderer->CurAnimation()->Reset();
	Renderer->AutoSpriteSizeOn();
	FlipX(_Dir);

}

void SkillEffect::Start()
{
	//std::shared_ptr<DamageActor> SkillDamage = GetLevel()->CreateActor<DamageActor>(ActorOrder::SkillEffect);
	
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetRenderOrder(RenderOrder::Effect);
	Renderer->CreateAnimation("FlashJump", "FlashJump", 0.1f, 0, 7, false);
	Renderer->CreateAnimation("LuckySeven", "LuckySeven", 0.1f, 0, 6, false);
	Renderer->CreateAnimation("HitSureken", "HitSureken", 0.1f, 0, 3, false);
	Renderer->CreateAnimation("ShowDownChallenge", "ShowDownChallenge", 0.07f,0,24,false);
	Off();
}

void SkillEffect::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Off();
	}
}
