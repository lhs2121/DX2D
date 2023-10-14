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
	if (GameEngineColor::RED == CurColor || GameEngineColor::BLUE == CurColor)//지면
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

void PhysicsActor::Horizontal(float _Delta)
{
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
	SetCurColor();
	float X = NetForce.X * _Delta;
	Transform.AddLocalPosition({ X,0 });

	float Y = NetForce.Y * _Delta;
	Transform.AddLocalPosition({ 0,Y });

	
	JumpCheck();
	GroundCheck();
	Gravity(_Delta);
	Horizontal(_Delta);
	BluePixelSnap();
	RedPixelSnap();
}