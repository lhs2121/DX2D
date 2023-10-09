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


float4 LuckySeven::GetBulletPos(float _OffSetX, float _OffSetY)
{
	float dir = Player::MainPlayer->GetDir();
	float4 BulletPos = Transform.GetWorldPosition() + float4(5 + _OffSetX * dir, 20 + _OffSetY);
	return BulletPos;
}

void LuckySeven::Start()
{
	Sureken1 = GetLevel()->CreateActor<ProJectile>(10);
	Sureken2 = GetLevel()->CreateActor<ProJectile>(11);

	Off();
}

void LuckySeven::Update(float _Delta)
{
	static bool IsJoinUpdate = true;

	if (IsJoinUpdate == true)
	{
		Sureken1->Transform.SetWorldPosition(GetBulletPos(1,4));
		Sureken1->SetDir(Player::MainPlayer->GetDir());
		Sureken1->SetCoolTime(1.0f);

		Sureken2->Transform.SetWorldPosition(GetBulletPos(2));
		Sureken2->SetDir(Sureken1->GetDir());
		Sureken2->SetCoolTime(1.0f);

		Sureken1->On();

		InterTime = MaxInterTime;
		CoolTime = MaxCoolTime;

		IsJoinUpdate = false;
	}
	
	if (InterTime > 0.0f)
	{
		InterTime -= _Delta;

		if (InterTime <= 0)
		{
			Sureken2->On();
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
