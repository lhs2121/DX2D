#include "PreCompile.h"
#include "DamageEffect.h"

DamageEffect::DamageEffect()
{
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::SetNumber(DamageColor _Color, int _RendererNum, int _SpriteNum)
{
	if (_RendererNum > RendererGroup.size() - 1)
	{
		std::shared_ptr <GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		RendererGroup.push_back(NewRenderer);
		RendererSize++;
	}
	switch (_Color)
	{
	case DamageColor::Orange:
		RendererGroup[_RendererNum]->SetSprite("AtkDmg", _SpriteNum);
		break;
	case DamageColor::Red:
		RendererGroup[_RendererNum]->SetSprite("CriDmg", _SpriteNum);
		break;
	case DamageColor::Purple:
		RendererGroup[_RendererNum]->SetSprite("HitDmg", _SpriteNum);
		break;
	default:
		break;
	}
	RendererGroup[_RendererNum]->On();
}

void DamageEffect::HorizontalAlign()
{
	for (int i = 0; i < RendererGroup.size(); i++)
	{
		RendererGroup[i]->Transform.AddLocalPosition({ 10.0f * i, 0.0f });
	}
}

void DamageEffect::VerticalAlign()
{
	for (int i = 0; i < RendererGroup.size(); i++)
	{
		if (i % 2 == 0)
		{
			RendererGroup[i]->Transform.AddLocalPosition({ 0.0f, 2.0f });
		}
	}
}

void DamageEffect::RenderOrderAlign(int _Order)
{
	for (int i = 0; i < RendererGroup.size(); i++)
	{
		RendererGroup[i]->SetRenderOrder(static_cast<int>(RenderOrder::Effect2) + i + _Order);
	}
}

void DamageEffect::Start()
{
	RendererGroup.reserve(RendererSize);
	for (size_t i = 0; i < RendererSize; i++)
	{
		std::shared_ptr <GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		NewRenderer->Off();
		RendererGroup.push_back(NewRenderer);
	}

	Off();
}

void DamageEffect::RenderStart()
{
	cool = 1.5f;
	On();
}

void DamageEffect::RenderEnd()
{
	for (int i = 0; i < RendererGroup.size(); i++)
	{
		RendererGroup[i]->Off();
		RendererGroup[i]->Transform.SetLocalPosition({ 0.0f,0.0f });
	}
	Transform.SetLocalPosition({ 0.0f,0.0f });
	Off();
}

void DamageEffect::Update(float _Delta)
{
	cool -= _Delta;
	if (cool <= 0)
	{
		RenderEnd();
	}
	Transform.AddLocalPosition(float4::UP * _Delta * 20.0f);
}

