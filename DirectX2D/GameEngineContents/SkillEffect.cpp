#include "PreCompile.h"
#include "SkillEffect.h"
#include "Player.h"

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

void SkillEffect::EffectSetting(float4 _Pos, EffectType _Type, float _Dir)
{
	int random = GameEngineRandom::GameEngineRandom().RandomInt(1, 30);

	float4 OffSet;

	switch (_Type)
	{
	case EffectType::FlashJump:
		OffSet = { _Dir * -15.0f,10.0f };
		Renderer->ChangeAnimation("FlashJump");
		break;
	case EffectType::LuckySeven:
		_Dir = Player::MainPlayer->GetDir();
		OffSet = { _Dir * 40.0f,30.0f };
		Renderer->ChangeAnimation("LuckySeven");
		break;
	case EffectType::HitSureken:
		OffSet = { _Dir * random,0.0f };
		Renderer->ChangeAnimation("HitSureken");
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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetRenderOrder(RenderOrder::Effect);
	Renderer->CreateAnimation("FlashJump", "FlashJump", 0.1f, 0, 7, false);
	Renderer->CreateAnimation("LuckySeven", "LuckySeven", 0.1f, 0, 6, false);
	Renderer->CreateAnimation("HitSureken", "HitSureken", 0.1f, 0, 3, false);
	Off();
}

void SkillEffect::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Off();
	}
}
