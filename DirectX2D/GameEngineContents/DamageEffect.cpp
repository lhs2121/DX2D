#include "PreCompile.h"
#include "DamageEffect.h"

DamageEffect::DamageEffect()
{
}

DamageEffect::~DamageEffect()
{
}

void DamageEffect::Start()
{
	Off();
}

void DamageEffect::Setting(float4 _Pos, DamageColor _Color, std::vector<int> _NumArray, int _Order, float _StartDelayTime, int _ID)
{
	for (size_t i = RendererGroup.size(); i < _NumArray.size(); i++)
	{
		std::shared_ptr <GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
		NewRenderer->Off();
		RendererGroup.push_back(NewRenderer);
	}

	for (int i = 0; i < _NumArray.size(); i++)
	{
		switch (_Color)
		{
		case DamageColor::Orange:
			if (i == 0)
			{
				RendererGroup[i]->SetSprite("Damage_Orange_Big", _NumArray[i]);
				break;
			}
			RendererGroup[i]->SetSprite("Damage_Orange", _NumArray[i]);
			break;
		case DamageColor::Red:
			if (i == 0)
			{
				RendererGroup[i]->SetSprite("Damage_Red_Big", _NumArray[i]);
				break;
			}
			RendererGroup[i]->SetSprite("Damage_Red", _NumArray[i]);
			break;
		case DamageColor::Purple:
			if (i == 0)
			{
				RendererGroup[i]->SetSprite("Damage_Purple_Big", _NumArray[i]);
				break;
			}
			RendererGroup[i]->SetSprite("Damage_Purple", _NumArray[i]);
			break;
		default:
			break;
		}

		RendererGroup[i]->Transform.AddLocalPosition({ 23.0f * i, 0.0f });


		if (i % 2 == 0)
		{
			RendererGroup[i]->Transform.AddLocalPosition({ 0.0f, 2.0f });
		}

		RendererGroup[i]->SetRenderOrder(i + _Order);
	}

	int RandomX = GameEngineRandom::GameEngineRandom().RandomInt(-10, 10);
	Transform.SetWorldPosition(_Pos + float4(static_cast<float>(RandomX), 0));
	StartDelayTime = _StartDelayTime;
	DamageID = _ID;
	CoolTime = 0.5f;
	if (StartDelayTime == 0.0f)
	{
		RendererOn();
	}
	On();
}

void DamageEffect::Update(float _Delta)
{
	if (StartDelayTime > 0.0f)
	{
		StartDelayTime -= _Delta;
		if (StartDelayTime <= 0.0f)
		{
			RendererOn();
		}
		return;
	}

	CoolTime -= _Delta;

	if (CoolTime <= 0.0f)
	{
		DamageID = -1;
		for (std::shared_ptr<GameEngineSpriteRenderer> Renderer : RendererGroup)
		{
			Renderer->GetColorData().MulColor.A -= _Delta;
		}
	}
	if (RendererGroup[0]->GetColorData().MulColor.A <= 0.0f)
	{
		RendererOff();
		Off();
	}

	Transform.AddWorldPosition(float4::UP * _Delta * 20.0f);
}

void DamageEffect::RendererOn()
{
	for (std::shared_ptr<GameEngineSpriteRenderer> Renderer : RendererGroup)
	{
		Renderer->On();
	}
}

void DamageEffect::RendererOff()
{
	for (std::shared_ptr<GameEngineSpriteRenderer> Renderer : RendererGroup)
	{
		Renderer->Off();
		Renderer->Transform.SetLocalPosition({ 0.0f,0.0f });
		Renderer->SetRenderOrder(0);
		Renderer->GetColorData().MulColor.A = 1.0f;
	}
}
