#include "PreCompile.h"
#include "DamageEffect.h"

DamageEffect::DamageEffect()
{
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::SetNumber(int RendererNumber,int _Value)
{
	if (RendererNumber > RendererSize - 1)
	{
		std::shared_ptr <GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		NewRenderer->SetRenderOrder(RenderOrder::Effect2);
		NewRenderer->Off();
		RendererGroup.push_back(NewRenderer);
		RendererSize++;
	}
	RendererGroup[RendererNumber]->SetSprite("AtkDmg", _Value);
	RendererGroup[RendererNumber]->On();
}

void DamageEffect::MoveRendererPos(int RendererNumber, float4 _Pos)
{
	RendererGroup[RendererNumber]->Transform.AddLocalPosition(_Pos);
}

void DamageEffect::SetRenderOrder(int RendererNumber, int _Order)
{
	RendererGroup[RendererNumber]->SetRenderOrder(_Order);
	CurOrder = _Order;
}

void DamageEffect::Start()
{
	RendererGroup.reserve(RendererSize);
	for (size_t i = 0; i < RendererSize; i++)
	{
		std::shared_ptr <GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		NewRenderer->SetRenderOrder(RenderOrder::Effect2);
		NewRenderer->Off();
		RendererGroup.push_back(NewRenderer);
	}
	
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
	for (size_t i = 0; i < RendererSize; i++)
	{
		RendererGroup[i]->Off();
		RendererGroup[i]->Transform.SetLocalPosition({ 0.0f,0.0f });
		RendererGroup[i]->SetRenderOrder(RenderOrder::Effect2);
	}
	
	CurOrder = int(RenderOrder::Effect2);
	Transform.SetLocalPosition({ 0.0f,0.0f });
}

void DamageEffect::Update(float _Delta)
{
	cool -= _Delta;
	if (cool <= 0)
	{
		EndEffect();
	}
	Transform.AddLocalPosition(float4::UP * _Delta * 20.0f);
}

