#include "PreCompile.h"
#include "PhysicsActor.h"
#include "KCityMap.h"

PhysicsActor::PhysicsActor()
{

}
PhysicsActor::~PhysicsActor()
{

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
	float4 Pos = Transform.GetWorldPosition();
	CurColor = KCityMap::MainMap->GetColor(Pos, GameEngineColor::ALAPA);

	if(GameEngineColor::RED == CurColor || GameEngineColor::BLUE == CurColor)//지면
	{
		IsGrounded = true;
	}
	else if (GameEngineColor::RED != CurColor && GameEngineColor::BLUE != CurColor) //공중
	{
		IsGrounded = false;
	}
}

void PhysicsActor::Gravity(float _Delta)
{
	if (IsGrounded == true)
	{
		if (IsJumping == false)
		{
			GravityForce.Y = 0.0f;
		}
	}
	else if (IsGrounded == false)
	{
		if (CanClimbRope == true)
		{
			GravityForce.Y = 0.0f;
		}
		else if (GravityForce.Y > -MaxGravity)
		{
			GravityForce.Y -= 1000.0f * _Delta;
		}
	}

	Transform.AddLocalPosition(GravityForce * _Delta);
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

	if (IsGrounded == false)
	{
		return;
	}

	if (CurColor == GameEngineColor::RED)
	{
		while (true)
		{
			float4 Pos = Transform.GetWorldPosition() + Pos2;
			GameEngineColor Color = KCityMap::MainMap->GetColor(Pos, GameEngineColor::RED);

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

	if (IsGrounded == false)
	{
		return;
	}

	if (CurColor == GameEngineColor::BLUE)
	{
		while (true)
		{
			float4 Pos = Transform.GetWorldPosition();
			GameEngineColor Color = KCityMap::MainMap->GetColor(Pos, GameEngineColor::ALAPA);

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

void PhysicsActor::Update(float _Delta)
{
	JumpCheck();
	GroundCheck();
	Gravity(_Delta);
	BluePixelSnap();
	RedPixelSnap();
}