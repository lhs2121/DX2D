#include "PreCompile.h"
#include "LuckySeven.h"
#include "ProJectile.h"
#include "Player.h"

LuckySeven::LuckySeven()
{
}

LuckySeven::~LuckySeven()
{
}

float4 LuckySeven::GetBulletPos()
{
	float4 BulletPos = Transform.GetWorldPosition() + float4(10 * Player::MainPlayer->GetDir(),10);
	return BulletPos;
}

void LuckySeven::Start()
{
	sureken1 = GetLevel()->CreateActor<ProJectile>(10);
	sureken2 = GetLevel()->CreateActor<ProJectile>(11);
}

void LuckySeven::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LSHIFT) && DoneFire1 == false && DoneFire2 == false)
	{
		sureken1->Transform.SetWorldPosition(GetBulletPos());
		sureken1->SetDir(Player::MainPlayer->GetDir());
		sureken1->On();		

		DoneFire1 = true;
	}

	if (DoneFire1 == true && DoneFire2 == false)
	{
		InterTime -= _Delta;

		if (InterTime <= 0)
		{
			sureken2->Transform.SetWorldPosition(GetBulletPos() + float4(10 * Player::MainPlayer->GetDir(), 10));
			sureken2->SetDir(Player::MainPlayer->GetDir());
			sureken2->On();
			DoneFire2 = true;
		}
	}

	if (sureken1->IsUpdate() == false)
	{
		DoneFire1 = false;
	}
	if (sureken2->IsUpdate() == false)
	{
		DoneFire2 = false;
	}
}
