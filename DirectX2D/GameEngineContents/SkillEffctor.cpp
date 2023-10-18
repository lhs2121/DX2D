#include "PreCompile.h"
#include "SkillEffctor.h"
#include "SkillEffect.h"
#include "Player.h"
SkillEffctor* SkillEffctor::Inst = nullptr;

SkillEffctor::SkillEffctor()
{
}

SkillEffctor::~SkillEffctor()
{
}

void SkillEffctor::StartEffect(float4 _Pos, EffectType _Type, float _Dir)
{
	std::list<std::shared_ptr<SkillEffect>> list;
	list = GetLevel()->GetObjectGroupConvert<SkillEffect>(ActorOrder::SkillEffect);
	std::shared_ptr<SkillEffect> NewEffect = GetUsableEffect(list);
	NewEffect->EffectSetting(_Pos, _Type, _Dir);
	NewEffect->On();
}

void SkillEffctor::Start()
{
	for (int i = 0; i < 10; i++)
	{
		GetLevel()->CreateActor<SkillEffect>(ActorOrder::SkillEffect);
	}
}

std::shared_ptr<SkillEffect> SkillEffctor::GetUsableEffect(std::list<std::shared_ptr<SkillEffect>> _list)
{
	std::list<std::shared_ptr<SkillEffect>>::iterator Start = _list.begin();
	std::list<std::shared_ptr<SkillEffect>>::iterator End = _list.end();
	
	for (; Start != End;Start++)
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

	std::shared_ptr<SkillEffect> NewEffect;
	NewEffect = GetLevel()->CreateActor<SkillEffect>(ActorOrder::SkillEffect);
	return NewEffect;
}

