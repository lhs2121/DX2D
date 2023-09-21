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
	Transform.AddLocalPosition(GravityForce * _Delta);

	if (IsGrounded == false)
	{
		if (GravityForce.Y > -MaxGravity)
		{
			GravityForce.Y -= 1000.0f * _Delta;
		}
	}
	else 
	{
		if (IsJumping == false)
		{
			GravityForce.Y = 0.0f;
		}
	}
}

void PhysicsActor::Jump()
{
	GravityForce.Y = JumpForce;
}

void PhysicsActor::RedPixelSnap()
{
	if (IsJumping == true)
	{
		return;
	}

	float4 Pos = Transform.GetWorldPosition() + Pos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (Color == GameEngineColor::RED)
	{
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

bool PhysicsActor::IsFall()
{
	if (IsJumping == false && IsGrounded == false)
	{
		return true;
	}

	return false;
}

void PhysicsActor::BluePixelSnap()
{
	if (IsJumping == true)
	{
		return;
	}

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

void PhysicsActor::JumpCheck()
{
	if (GravityForce.Y <= 0)
	{
		IsJumping = false;
	}
	else if (GravityForce.Y > 0)
	{
		IsJumping = true;
	}
}

void PhysicsActor::GroundCheck()
{
	float4 Pos = Transform.GetWorldPosition() + Pos1;
	GameEngineColor Color = BackGround::MainMap->GetColor(Pos, GameEngineColor::RED);

	if (GameEngineColor::RED != Color && GameEngineColor::BLUE != Color) //공중
	{
		IsGrounded = false;
	}
	else  //지면
	{
		IsGrounded = true;
	}
}

void PhysicsActor::Update(float _Delta)
{
	JumpCheck();
	GroundCheck();
	Gravity(_Delta);
	BluePixelSnap();
	RedPixelSnap();
}