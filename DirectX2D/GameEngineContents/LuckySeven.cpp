#include "PreCompile.h"
#include "LuckySeven.h"
#include "ProJectile.h"
#include "Player.h"

LuckySeven* LuckySeven::Inst = nullptr;

LuckySeven::LuckySeven()
{
	Inst = this;
}

LuckySeven::~LuckySeven()
{

}


float4 LuckySeven::GetBulletPos(float4 _OffSet)
{
	float dir = Player::MainPlayer->GetDir();
	float4 BulletPos = Player::MainPlayer->Transform.GetWorldPosition()
	+ float4(_OffSet.X * dir, _OffSet.Y);
	return BulletPos;
}

void LuckySeven::Start()
{
	Bullet1 = GetLevel()->CreateActor<ProJectile>(55);
	Bullet2 = GetLevel()->CreateActor<ProJectile>(55);
	Bullet3 = GetLevel()->CreateActor<ProJectile>(55);
	Bullet4 = GetLevel()->CreateActor<ProJectile>(55);
	Off();
}

void LuckySeven::Update(float _Delta)
{
	if (IsJoinUpdate == true)
	{
		if (FirstBullet == Bullet3 || FirstBullet == nullptr)
		{
			FirstBullet = Bullet1;
			SecondBullet = Bullet2;
			BulletSetting();
			FirstBullet->On();
		}
		else if (FirstBullet == Bullet1)
		{
			FirstBullet = Bullet3;
			SecondBullet = Bullet4;
			BulletSetting();
			FirstBullet->On();
		}
		InterTime = MaxInterTime;
		CoolTime = MaxCoolTime;

		IsJoinUpdate = false;
	}
	if (InterTime > 0.0f)
	{
		InterTime -= _Delta;
		if (InterTime <= 0)
		{
			SecondBullet->On();
		}
	}
	if (CoolTime > 0.0f)
	{
		CoolTime -= _Delta;
		if (CoolTime <= 0)
		{
			IsJoinUpdate = true;
			Off();
		}
	}

}

void LuckySeven::BulletSetting()
{
	
	FirstBullet->Transform.SetWorldPosition(GetBulletPos(BulletPosOffset1));
	FirstBullet->SetDir(Player::MainPlayer->GetDir());
	FirstBullet->SetCoolTime(BulletCoolTime);
	FirstBullet->SetSpeed(BulletSpeed);

	SecondBullet->Transform.SetWorldPosition(GetBulletPos(BulletPosOffset2));
	SecondBullet->SetDir(FirstBullet->GetDir());
	SecondBullet->SetCoolTime(BulletCoolTime);
	SecondBullet->SetSpeed(BulletSpeed);
}


