#include "PreCompile.h"
#include "SkillManager.h"
#include "SkillEffect.h"
#include "Player.h"
SkillManager* SkillManager::Inst = nullptr;

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

void SkillManager::StartSkill(float4 _Pos, SkillType _Type, float _Dir)
{
	std::list<std::shared_ptr<SkillEffect>> list;
	list = GetLevel()->GetObjectGroupConvert<SkillEffect>(ActorOrder::SkillEffect);
	std::shared_ptr<SkillEffect> NewEffect = GetUsableEffect(list);
	NewEffect->EffectSetting(_Pos, _Type, _Dir);
	NewEffect->On();
}

void SkillManager::Start()
{
	for (int i = 0; i < 10; i++)
	{
		GetLevel()->CreateActor<SkillEffect>(ActorOrder::SkillEffect);
	}
}

std::shared_ptr<SkillEffect> SkillManager::GetUsableEffect(std::list<std::shared_ptr<SkillEffect>> _list)
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

