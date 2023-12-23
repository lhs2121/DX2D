#include "PreCompile.h"
#include "LevelUpEffect.h"
#include "Player.h"

LevelUpEffect::LevelUpEffect()
{
}

LevelUpEffect::~LevelUpEffect()
{
}

void LevelUpEffect::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->SetRenderOrder(RenderOrder::Effect2);
		Renderer->CreateAnimation("LevelUpEffect", "LevelUpEffect");
		Renderer->ChangeAnimation("LevelUpEffect");
		Renderer->SetEndEvent("LevelUpEffect",
			[&](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			});
		Renderer->AutoSpriteSizeOn();
		Renderer->Transform.SetLocalPosition({ 0,120 });
	}
}

void LevelUpEffect::Update(float _Delta)
{
	Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
}
