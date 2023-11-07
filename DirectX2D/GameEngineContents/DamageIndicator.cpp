#include "PreCompile.h"
#include "DamageIndicator.h"
#include "DamageEffect.h"

DamageIndicator::DamageIndicator()
{
}

DamageIndicator::~DamageIndicator()
{

}

void DamageIndicator::RenderDamage(float4 _Pos, DamageColor _Color, std::vector<float> _DamageGroup, int _DamageID)
{
	std::list<std::shared_ptr<GameEngineObject>> list = GetLevel()->GetObjectGroup(ActorOrder::DamageEffect);
	for (int i = 0; i < _DamageGroup.size(); i++)
	{
		std::shared_ptr<DamageEffect> NewEffect = GetNonUpdateObject(list);

		float4 StartPos = _Pos + float4(0.0f, 30.0f * i);

		if (PrevEffect != nullptr && PrevEffect->GetID() == _DamageID)
		{
			StartPos = PrevEffect->Transform.GetWorldPosition() + float4(0.0f, 30.0f);
		}

		std::vector<int> Damage = GetIntArray(_DamageGroup[i]);

		LastRenderOrder += i + 7;
		float StartDelay = 0.1f * i;

		NewEffect->Setting(StartPos, _Color, Damage, LastRenderOrder, StartDelay, _DamageID);

		PrevEffect = NewEffect;
	}
}

std::vector<int> DamageIndicator::GetIntArray(float _Value)
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

std::shared_ptr<DamageEffect> DamageIndicator::GetNonUpdateObject(std::list<std::shared_ptr<GameEngineObject>> _list)
{
	std::list<std::shared_ptr<GameEngineObject>>::iterator Start = _list.begin();
	std::list<std::shared_ptr<GameEngineObject>>::iterator End = _list.end();

	for (; Start != End; Start++)
	{
		if ((*Start)->IsUpdate() == true)
		{
			continue;
		}
		else
		{
			return (*Start)->GetDynamic_Cast_This<DamageEffect>();
		}
	}

	return GetLevel()->CreateActor<DamageEffect>(ActorOrder::DamageEffect);
}

void DamageIndicator::Start()
{
}