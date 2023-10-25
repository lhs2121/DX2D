#include "PreCompile.h"
#include "SurekenShooter.h"
#include "Sureken.h"
#include "Player.h"
#include "StatManager.h"

SurekenShooter* SurekenShooter::Inst = nullptr;

SurekenShooter::SurekenShooter()
{

}

SurekenShooter::~SurekenShooter()
{

}


float4 SurekenShooter::GetSurekenPos(float4 _OffSet)
{
	float dir = Player::MainPlayer->GetDir();
	float4 SurekenPos = Player::MainPlayer->Transform.GetWorldPosition() + float4(_OffSet.X * dir, _OffSet.Y);
	return SurekenPos;
}

void SurekenShooter::Start()
{
	Sureken1 = GetLevel()->CreateActor<Sureken>(ActorOrder::Sureken);
	Sureken2 = GetLevel()->CreateActor<Sureken>(ActorOrder::Sureken);
	Sureken3 = GetLevel()->CreateActor<Sureken>(ActorOrder::Sureken);
	Sureken4 = GetLevel()->CreateActor<Sureken>(ActorOrder::Sureken);
	Off();
}

void SurekenShooter::Update(float _Delta)
{
	if (IsReady == false)
	{
		if (FirstSureken == Sureken3 || FirstSureken == nullptr)
		{
			FirstSureken = Sureken1;
			SecondSureken = Sureken2;
			SurekenSetting();
			FirstSureken->StartFire();
		}
		else if (FirstSureken == Sureken1)
		{
			FirstSureken = Sureken3;
			SecondSureken = Sureken4;
			SurekenSetting();
			FirstSureken->StartFire();
		}
		InterTime = MaxInterTime;
		CoolTime = MaxCoolTime;

		IsReady = true;
	}

	if (InterTime > 0.0f)
	{
		InterTime -= _Delta;
		if (InterTime <= 0)
		{
			SecondSureken->StartFire();
		}
	}
	if (CoolTime > 0.0f)
	{
		CoolTime -= _Delta;
		if (CoolTime <= 0)
		{
			IsReady = false;
			Off();
		}
	}

}

void SurekenShooter::SurekenSetting()
{
	FirstSureken->Transform.SetWorldPosition(GetSurekenPos(SurekenPosOffset1));
	FirstSureken->SetDir(Player::MainPlayer->GetDir());
	FirstSureken->SetCoolTime(SurekenCoolTime);
	FirstSureken->SetSpeed(SurekenSpeed);
	StatManager::Inst->SetDamage(Player::MainPlayer->GetStat().get(), FirstSureken->GetDynamic_Cast_This<DamageActor>().get());

	SecondSureken->Transform.SetWorldPosition(GetSurekenPos(SurekenPosOffset2));
	SecondSureken->SetDir(FirstSureken->GetDir());
	SecondSureken->SetCoolTime(SurekenCoolTime);
	SecondSureken->SetSpeed(SurekenSpeed);
	StatManager::Inst->SetDamage(Player::MainPlayer->GetStat().get(), SecondSureken->GetDynamic_Cast_This<DamageActor>().get());
}


