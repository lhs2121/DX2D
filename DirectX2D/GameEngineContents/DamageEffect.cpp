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

void DamageEffect::StartEffect()
{
	cool = 1.5f;
	On();
}

void DamageEffect::EndEffect()
{
	Off();
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	CurOrder = int(RenderOrder::Effect2);
	Renderer->Transform.SetLocalPosition({ 0.0f,0.0f });
}

void DamageEffect::Update(float _Delta)
{
	cool -= _Delta;
	if (cool <= 0)
	{
		EndEffect();
	}
	Renderer->Transform.AddLocalPosition(float4::UP * _Delta * 20.0f);
}

