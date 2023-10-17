#include "PreCompile.h"
#include "PhysicsActor.h"
#include "MapleMap.h"

PhysicsActor::PhysicsActor()
{

}
PhysicsActor::~PhysicsActor()
{

}

GameEngineColor PhysicsActor::GetColor(float4 _Pos)
{
	return MapleMap::CurMap->GetColor(_Pos, GameEngineColor::ALAPA);
}

void PhysicsActor::SetCurColor()
{
	CurColor = GetColor(Transform.GetWorldPosition());
}

void PhysicsActor::GroundCheck()
{
	if (GameEngineColor::RED == CurColor || GameEngineColor::BLUE == CurColor)//����
	{
		IsGrounded = true;
	}
	else if (GameEngineColor::RED != CurColor && GameEngineColor::BLUE != CurColor) //����
	{
		IsGrounded = false;
	}
}

void PhysicsActor::JumpCheck()
{
	if (NetForce.Y <= 0)
	{
		IsJumping = false;
	}
	else if (NetForce.Y > 0)
	{
		IsJumping = true;
	}
}

void PhysicsActor::Gravity(float _Delta)
{
	if (IsGrounded == true)
	{
		if (IsJumping == false)
		{
			NetForce.Y = 0.0f;
		}
	}
	else if (IsGrounded == false)
	{
		if (NetForce.Y > -MaxGravity)
		{
			NetForce.Y -= 1000.0f * _Delta;
		}
	}
}

void PhysicsActor::Breaking(float _Delta)
{
	if (IsGrounded == true)
	{
		BrakingXForce = 2300.0f;
	}
	else
	{
		BrakingXForce = 300.0f;
	}
	if (NetForce.X > 0)
	{
		NetForce.X -= BrakingXForce * _Delta;

		if (NetForce.X < 0)
		{
			NetForce.X = 0;
		}
	}
	else if (NetForce.X < 0)
	{
		NetForce.X += BrakingXForce * _Delta;

		if (NetForce.X > 0)
		{
			NetForce.X = 0;
		}
	}
}

void PhysicsActor::RedPixelSnap()
{
	if (IsGrounded == false)
	{
		return;
	}

	if (CurColor == GameEngineColor::RED)
	{
		while (true)
		{
			GameEngineColor Color = GetColor(Transform.GetWorldPosition() + float4(0, 1));
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
			GameEngineColor Color = GetColor(Transform.GetWorldPosition());
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
	Transform.AddLocalPosition(NetForce * _Delta);
	SetCurColor();
	JumpCheck();
	GroundCheck();
	Gravity(_Delta);
	Breaking(_Delta);
	BluePixelSnap();
	RedPixelSnap();
}