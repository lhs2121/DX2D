#include "PreCompile.h"
#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::FlipX(int _dir)
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

void Effect::ChangeAnimation(std::string _String)
{
	Renderer->ChangeAnimation(_String);
	Renderer->CurAnimation()->Reset();
}

void Effect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	Renderer->CreateAnimation("FlashJump", "FlashJump", 0.1f, 0, 9, false);
	Renderer->CreateAnimation("LuckySeven", "LuckySeven", 0.1f, 0, 6, false);
	Renderer->CreateAnimation("HitSureken", "HitSureken", 0.1f, 0, 3, false);
	Renderer->AutoSpriteSizeOn();

	Off();
}

void Effect::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Off();
		Renderer->CurAnimation()->Reset();
	}
}
