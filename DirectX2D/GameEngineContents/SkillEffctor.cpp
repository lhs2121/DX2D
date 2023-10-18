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
	std::shared_ptr<SkillEffect> Effect = GetUsableEffect(list);

	int random = GameEngineRandom::GameEngineRandom().RandomInt(1, 30);
	float4 OffSet;
	std::string AnimationName;
	switch (_Type)
	{
	case EffectType::FlashJump:
		OffSet = { _Dir * -15.0f,10.0f };
		AnimationName = "FlashJump";
		break;
	case EffectType::LuckySeven:
		/*if (IsAleadyOnEffect(list))
		{
			return;
		}*/
		_Dir = Player::MainPlayer->GetDir();
		OffSet = { _Dir * 40.0f,30.0f };
		AnimationName = "LuckySeven";
		break;
	case EffectType::HitSureken:
		OffSet = { _Dir * random,0.0f };
		AnimationName = "HitSureken";
		break;
	default:
		break;
	}

	Effect->Transform.SetWorldPosition(_Pos + OffSet);
	Effect->ChangeAnimation(AnimationName);
	Effect->FlipX(_Dir);
	Effect->On();
}



void SkillEffctor::Start()
{
	for (int i = 0; i < 10; i++)
	{
		GetLevel()->CreateActor<SkillEffect>(ActorOrder::SkillEffect);
	}
}

void SkillEffctor::Update(float _Delta)
{

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

