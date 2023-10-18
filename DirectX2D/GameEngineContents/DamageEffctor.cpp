#include "PreCompile.h"
#include "DamageEffctor.h"
#include "DamageEffect.h"

DamageEffctor::DamageEffctor()
{
}

DamageEffctor::~DamageEffctor()
{
}


void DamageEffctor::StartEffect(float4 _Pos, float _DamageValue)
{
	PrevGruopPos = _Pos;
	if (PrevEffect!= nullptr && PrevEffect->GetCoolTime() <= 1.2f)
	{
		Stack = 1;
	}
	else
	{
		Stack += 1;
	}

	float4 SpawnPos = PrevGruopPos + float4(0.0f, 30.0f * Stack) + GameEngineRandom::GameEngineRandom().RandomFloat(-10, 10);
	
	if (Stack > 8)
	{
		Stack = 0;
	}

    std::vector<int> NumArray; 
    std::string StrValue = std::to_string(static_cast<int>(_DamageValue)); 
    NumArray.reserve(StrValue.size());
    for (size_t i = 0; i < StrValue.size(); i++)
    {
        NumArray.push_back(static_cast<int>(StrValue[i] - '0')); 
    }
    //NumArray에 데미지 한자릿수씩 들어가있음

    std::list<std::shared_ptr<DamageEffect>> list;
    list = GetLevel()->GetObjectGroupConvert<DamageEffect>(ActorOrder::DamageEffect);

	for (int i = 0; i < NumArray.size(); i++)
	{
		float4 NextPos;
		if (i % 2 == 0)
		{
			NextPos = { 20.0f * i, 0.0f };
		}
		else
		{
			NextPos = { 20.0f * i, -3.0f };
		}
		std::shared_ptr<DamageEffect> NewEffect = GetUsableEffect(list);

		NewEffect->Transform.SetWorldPosition(SpawnPos);
		NewEffect->MovePos(NextPos);
		if (PrevEffect != nullptr)
		{
			int order = PrevEffect->CurOrder + 1;
			NewEffect->SetRenderOrder(order);
		}
		else
		{
			int order = int(RenderOrder::Effect2);
			NewEffect->SetRenderOrder(order);
		}
		NewEffect->SetNumber(NumArray[i]);
		NewEffect->On();


		PrevEffect = NewEffect;
	}

}

void DamageEffctor::Start()
{
    for (int i = 0; i < 100; i++)
    {
        GetLevel()->CreateActor<DamageEffect>(ActorOrder::DamageEffect);
    }
 
}

void DamageEffctor::Update(float _Delta)
{
}


std::shared_ptr<DamageEffect> DamageEffctor::GetUsableEffect(std::list<std::shared_ptr<DamageEffect>> _list)
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