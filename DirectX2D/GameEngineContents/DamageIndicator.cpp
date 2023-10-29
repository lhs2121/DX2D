#include "PreCompile.h"
#include "DamageIndicator.h"
#include "DamageEffect.h"

DamageIndicator::DamageIndicator()
{
}

DamageIndicator::~DamageIndicator()
{

}


void DamageIndicator::RenderDamage(float4 _Pos, DamageColor _Color)
{
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