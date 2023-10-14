#include "PreCompile.h"
#include "BulletShooter.h"
#include "ProJectile.h"
#include "Player.h"

BulletShooter* BulletShooter::Inst = nullptr;

BulletShooter::BulletShooter()
{
	Inst = this;
}

BulletShooter::~BulletShooter()
{

}


float4 BulletShooter::GetBulletPos(float4 _OffSet)
{
	float dir = Player::MainPlayer->GetDir();
	float4 BulletPos = Player::MainPlayer->Transform.GetWorldPosition()
	+ float4(_OffSet.X * dir, _OffSet.Y);
	return BulletPos;
}

void BulletShooter::Start()
{
	Bullet1 = GetLevel()->CreateActor<ProJectile>(ActorOrder::Projectile);
	Bullet2 = GetLevel()->CreateActor<ProJectile>(ActorOrder::Projectile);
	Bullet3 = GetLevel()->CreateActor<ProJectile>(ActorOrder::Projectile);
	Bullet4 = GetLevel()->CreateActor<ProJectile>(ActorOrder::Projectile);
	Off();
}

void BulletShooter::Update(float _Delta)
{
	if (IsReady == false)
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

		IsReady = true;
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
			IsReady = false;
			Off();
		}
	}

}

void BulletShooter::BulletSetting()
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


