#include "PreCompile.h"
#include "PhysicsActor.h"
#include "MapleMap.h"

PhysicsActor::PhysicsActor()
{

}
PhysicsActor::~PhysicsActor()
{

}


void PhysicsActor::SetModuleEnabled(bool _EnableNetForce, bool _EnableCurColor, bool _EnableJumpCheck, bool _EnableGroundCheck,
	bool _EnableGravity, bool _EnableBreaking, bool _EnableBluePixelSnap, bool _EnableRedPixelSnap, bool _EnableLimitToMapBounds)
{
	EnableNetForce = _EnableNetForce;
	EnableCurColor = _EnableCurColor;
	EnableJumpCheck = _EnableJumpCheck;
	EnableGroundCheck = _EnableGroundCheck;
	EnableGravity = _EnableGravity;
	EnableBreaking = _EnableBreaking;
	EnableBluePixelSnap = _EnableBluePixelSnap;
	EnableRedPixelSnap = _EnableRedPixelSnap;
	EnableLimitToMapBounds = _EnableLimitToMapBounds;
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

void PhysicsActor::LimitToMapBounds()
{
	float4 Pos = Transform.GetWorldPosition();
	float4 MapScale = MapleMap::CurMap->GetMapScale();
	if (Pos.X < 0.0f)
	{
		Transform.SetWorldPosition({ 0.0f,Pos.Y });
	}
	if (Pos.X > MapScale.X)
	{
		Transform.SetWorldPosition({ MapScale.X - 1.0f,Pos.Y });
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
	// 기본적인 체크들
	if (EnableLimitToMapBounds)
	{
		LimitToMapBounds();
	}
	if (EnableCurColor)
	{
		SetCurColor();
	}
	if (EnableJumpCheck)
	{
		JumpCheck();
	}
	if (EnableGroundCheck)
	{
		GroundCheck();
	}
	if (EnableBluePixelSnap)
	{
		BluePixelSnap();
	}
	if (EnableRedPixelSnap)
	{
		RedPixelSnap();
	}
	// 좌표이동 시작
	if (EnableNetForce)
	{
		Transform.AddLocalPosition(NetForce * _Delta);
	}
	if (EnableBreaking)
	{
		Breaking(_Delta);
	}
	if (EnableGravity)
	{
		Gravity(_Delta);
	}
}