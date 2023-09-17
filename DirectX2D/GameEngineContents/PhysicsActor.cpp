#include "PreCompile.h"
#include "PhysicsActor.h"
#include "BackGround.h"

PhysicsActor::PhysicsActor()
{

}
PhysicsActor::~PhysicsActor()
{

}

void PhysicsActor::SetFootPos(float4 _Pos1, float4 _Pos2)
{
	Pos1 = _Pos1;
	Pos2 = _Pos2;
}

void PhysicsActor::Gravity(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition() + Pos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		Transform.AddLocalPosition(GravityForce * _Delta);

		if (GravityForce.Y > -GlobalValue::MaxGravity)
		{
			GravityForce.Y -= 1000.0f * _Delta;
		}
	}
}

void PhysicsActor::RedPixelSnap()
{
	float4 Pos = Transform.GetWorldPosition() + Pos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (Color == GameEngineColor::RED)
	{
		GravityForce.Y = 0.0f;

		while (true)
		{
			float4 Pos = Transform.GetWorldPosition() + Pos2;
			GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

			if (Color == GameEngineColor::RED)
			{
				Transform.AddLocalPosition(float4::UP);
			}
			else if (Color != GameEngineColor::RED)
			{
				break;
			}
		}
	}

}

void PhysicsActor::BluePixelSnap()
{
	float4 Pos = Transform.GetWorldPosition() + Pos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (Color == GameEngineColor::BLUE)
	{
		while (true)
		{
			float4 Pos = Transform.GetWorldPosition() + Pos1;
			GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

			if (Color == GameEngineColor::BLUE)
			{
				Transform.AddLocalPosition(float4::DOWN);
			}
			else if (Color != GameEngineColor::BLUE)
			{
				break;
			}
		}
	}
}