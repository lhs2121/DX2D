#include "PreCompile.h"
#include "DamageEffect.h"

DamageEffect::DamageEffect()
{
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::SetNumber(int _Value)
{
	Renderer->SetSprite("AtkDmg", _Value);
}

void DamageEffect::MovePos(float4 _Pos)
{
	Renderer->Transform.AddLocalPosition(_Pos);
}

void DamageEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	Off();
}

void DamageEffect::Update(float _Delta)
{
	cool -= _Delta;
	if (cool <= 0)
	{
		Off();
		Renderer->Transform.SetLocalPosition({ 0,0 });
	}
	Renderer->Transform.AddLocalPosition(float4::UP * _Delta * 20.0f);
}

void DamageEffect::On()
{
	GameEngineActor::On();
	cool = 1.5f;
}
