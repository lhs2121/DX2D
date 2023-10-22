#include "PreCompile.h"
#include "DamageEffectController.h"
#include "DamageEffect.h"

DamageEffectController::DamageEffectController()
{
}

DamageEffectController::~DamageEffectController()
{
}


void DamageEffectController::StartEffect(float4 _Pos, float _DamageValue)
{
	CountStack();

	float4 StartPos;
	float4 OffsetY = float4(0.0f, 30.0f * CurStack);
	float RandomOffset = GameEngineRandom::GameEngineRandom().RandomFloat(-5, 5);
	float4 SpawnPos = _Pos + OffsetY + RandomOffset;

	PrevSpawnPos = _Pos;

	std::vector<int> NewArray = GetIntArray(_DamageValue);

	std::list<std::shared_ptr<DamageEffect>> list;

	list = GetLevel()->GetObjectGroupConvert<DamageEffect>(ActorOrder::DamageEffect);

	std::shared_ptr<DamageEffect> NewEffect = GetUsableEffect(list);

	NewEffect->Transform.SetWorldPosition(SpawnPos);

	for (int i = 0; i < NewArray.size(); i++)
	{

		NewEffect->SetNumber(i, NewArray[i]);

		float4 RendererOffset;

		if (i % 2 == 0)
		{
			RendererOffset = { 20.0f * i, 0.0f };
		}
		else
		{
			RendererOffset = { 20.0f * i, -3.0f };
		}

		NewEffect->MoveRendererPos(i, RendererOffset);

		if (PrevEffect != nullptr)
		{
			int order = PrevEffect->CurOrder + 1;
			NewEffect->SetRenderOrder(i, order);
		}
		else
		{
			int order = int(RenderOrder::Effect2);
			NewEffect->SetRenderOrder(i, order);
		}
	}
	NewEffect->Transform.AddWorldPosition({ -8.0f * NewArray.size() -1,0 });
	NewEffect->StartEffect();

	PrevEffect = NewEffect;

}

void DamageEffectController::CountStack()
{
	if (PrevEffect != nullptr && PrevEffect->GetCoolTime() <= 1.2f)
	{
		CurStack = 1;
	}
	else
	{
		CurStack += 1;
		if (CurStack > 8)
		{
			CurStack = 0;
		}
	}
}

float4 DamageEffectController::GetSpawnPos(float4 _Pos)
{
	float4 StartPos;
	StartPos = (PrevEffect != nullptr) ? PrevSpawnPos : _Pos;
	float4 OffsetY = float4(0.0f, 30.0f * CurStack);
	float RandomOffset = GameEngineRandom::GameEngineRandom().RandomFloat(-5, 5);
	float4 SpawnPos = StartPos + OffsetY + RandomOffset;
	return SpawnPos;
}

std::vector<int> DamageEffectController::GetIntArray(float _Value)
{
	std::vector<int> IntArray;

	int Value = static_cast<int>(_Value);

	std::string StrValue = std::to_string(Value);

	IntArray.reserve(StrValue.size());

	for (size_t i = 0; i < StrValue.size(); i++)
	{
		IntArray.push_back(static_cast<int>(StrValue[i] - '0'));
	}

	return IntArray;
}

std::shared_ptr<DamageEffect> DamageEffectController::GetUsableEffect(std::list<std::shared_ptr<DamageEffect>> _list)
{
	std::list<std::shared_ptr<DamageEffect>>::iterator Start = _list.begin();
	std::list<std::shared_ptr<DamageEffect>>::iterator End = _list.end();

	for (; Start != End; Start++)
	{
		if ((*Start)->IsUpdate() == true)
		{
			continue;
		}
		else
		{
			return (*Start);
		}
	}

	std::shared_ptr<DamageEffect> NewEffect;
	NewEffect = GetLevel()->CreateActor<DamageEffect>(ActorOrder::DamageEffect);
	return NewEffect;
}

void DamageEffectController::Start()
{


}