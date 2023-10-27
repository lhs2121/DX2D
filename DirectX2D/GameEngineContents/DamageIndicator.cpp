#include "PreCompile.h"
#include "DamageIndicator.h"
#include "DamageEffect.h"

DamageIndicator::DamageIndicator()
{
}

DamageIndicator::~DamageIndicator()
{

}


void DamageIndicator::RenderDamage(float4 _Pos, float _DamageValue, int _HitCount, DamageColor _Color)
{
	if (_DamageValue < 0)
	{
		return;
	}

	std::vector<int> NewArray = GetIntArray(_DamageValue);

	std::list<std::shared_ptr<DamageEffect>> list;
	list = GetLevel()->GetObjectGroupConvert<DamageEffect>(ActorOrder::DamageEffect);

	float4 PrevPos = _Pos;
	int PrevRenderOrder = 0;



	for (int j = 0; j < 5; j++)
	{
		std::shared_ptr<DamageEffect> DamageNumber = GetNonUpdateObject(list);

		for (int i = 0; i < NewArray.size(); i++)
		{
			DamageNumber->SetNumber(_Color, i, NewArray[i]);
			DamageNumber->HorizontalAlign();
			DamageNumber->VerticalAlign();
		}
		DamageNumber->Transform.SetWorldPosition(PrevPos + float4(0.0f, 20.0f));
		PrevPos = DamageNumber->Transform.GetWorldPosition();
		DamageNumber->RenderOrderAlign(j);
		DamageNumber->RenderStart();
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

std::shared_ptr<DamageEffect> DamageIndicator::GetNonUpdateObject(std::list<std::shared_ptr<DamageEffect>> _list)
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

	return GetLevel()->CreateActor<DamageEffect>(ActorOrder::DamageEffect);
}

void DamageIndicator::Start()
{
}