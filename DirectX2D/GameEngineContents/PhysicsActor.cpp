#include "PreCompile.h"
#include "PhysicsActor.h"
#include "KCityMap.h"

PhysicsActor::PhysicsActor()
{

}
PhysicsActor::~PhysicsActor()
{

}

GameEngineColor PhysicsActor::CalCulateColor(float4 _Pos)
{
	return KCityMap::MainMap->GetColor(_Pos, GameEngineColor::ALAPA);
}

void PhysicsActor::GroundCheck()
{
	CurColor = CalCulateColor(Transform.GetWorldPosition());

	if(GameEngineColor::RED == CurColor || GameEngineColor::BLUE == CurColor)//지면
	{
		IsGrounded = true;
	}
	else if (GameEngineColor::RED != CurColor && GameEngineColor::BLUE != CurColor) //공중
	{
		IsGrounded = false;
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

bool PhysicsActor::IsFall()
{
	if (IsJumping == false && IsGrounded == false)
	{
		return true;
	}

	return false;
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
		if (GravityForce.Y > -MaxGravity)
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
			GameEngineColor Color = CalCulateColor(Transform.GetWorldPosition() + Pos2);
			if (Color == GameEngineColor::RED)
			{
				Transform.AddLocalPosition(float4::UP);
			}
			else
			{
				break;
			}
		}
	}
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
			GameEngineColor Color = CalCulateColor(Transform.GetWorldPosition());
			if (Color == GameEngineColor::BLUE)
			{
				Transform.AddLocalPosition(float4::DOWN);
			}
			else
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
	if (ApplyGravity == true)
	{
		Gravity(_Delta);
	}
	BluePixelSnap();
	RedPixelSnap();
}