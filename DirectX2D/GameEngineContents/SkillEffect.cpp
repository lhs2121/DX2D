#include "PreCompile.h"
#include "SkillEffect.h"

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

void SkillEffect::ChangeAnimation(std::string _String)
{
	Renderer->ChangeAnimation(_String);
	Renderer->CurAnimation()->Reset();
}

void SkillEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetRenderOrder(RenderOrder::Effect);
	Renderer->CreateAnimation("FlashJump", "FlashJump", 0.1f, 0, 7, false);
	Renderer->CreateAnimation("LuckySeven", "LuckySeven", 0.1f, 0, 6, false);
	Renderer->CreateAnimation("HitSureken", "HitSureken", 0.1f, 0, 3, false);
	Renderer->AutoSpriteSizeOn();

	Off();
}

void SkillEffect::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Off();
	}
}
