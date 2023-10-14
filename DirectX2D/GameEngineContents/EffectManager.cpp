#include "PreCompile.h"
#include "EffectManager.h"
#include "Effect.h"
#include "Player.h"
EffectManager* EffectManager::Inst = nullptr;

EffectManager::EffectManager()
{
	Inst = this;
}

EffectManager::~EffectManager()
{
}

void EffectManager::StartEffect(float4 _Pos, EffectType _Type, float _Dir)
{
	std::list<std::shared_ptr<Effect>> list;
	list = GetLevel()->GetObjectGroupConvert<Effect>(ActorOrder::Effect);
	std::shared_ptr<Effect> Effect = GetUsableEffect(list);

	int random = GameEngineRandom::GameEngineRandom().RandomInt(1, 30);
	float4 OffSet;
	std::string Ani;
	switch (_Type)
	{
	case EffectType::FlashJump:
		OffSet = { _Dir * -15.0f,10.0f };
		Ani = "FlashJump";
		break;
	case EffectType::LuckySeven:
		if (IsAleadyOnEffect(list))
		{
			return;
		}
		_Dir = Player::MainPlayer->GetDir();
		OffSet = { _Dir * 40.0f,30.0f };
		Ani = "LuckySeven";
		break;
	case EffectType::HitSureken:
		OffSet = { _Dir * random,0.0f };
		Ani = "HitSureken";
		break;
	default:
		break;
	}

	Effect->Transform.SetWorldPosition(_Pos + OffSet);
	Effect->ChangeAnimation(Ani);
	Effect->FlipX(_Dir);
	Effect->On();
}



void EffectManager::Start()
{
	for (int i = 0; i < 10; i++)
	{
		GetLevel()->CreateActor<Effect>(ActorOrder::Effect);
	}
}

void EffectManager::Update(float _Delta)
{

}

std::shared_ptr<Effect> EffectManager::GetUsableEffect(std::list<std::shared_ptr<Effect>> _list)
{
	std::list<std::shared_ptr<Effect>>::iterator Start = _list.begin();
	std::list<std::shared_ptr<Effect>>::iterator End = _list.end();
	
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

	std::shared_ptr<Effect> NewEffect;
	NewEffect = GetLevel()->CreateActor<Effect>(ActorOrder::Effect);
	return NewEffect;
}

bool EffectManager::IsAleadyOnEffect(std::list<std::shared_ptr<Effect>> _list)
{
	std::list<std::shared_ptr<Effect>>::iterator Start = _list.begin();
	std::list<std::shared_ptr<Effect>>::iterator End = _list.end();

	for (; Start != End; Start++)
	{
		if ((*Start)->IsUpdate() == true)
		{
			return true;
		}
		else
		{
			continue;
		}
	}

	return false;
}

