#pragma once
#include "MapleActor.h"

// ���� :
class PhysicsActor : public MapleActor
{
public:
	// constrcuter destructer
	PhysicsActor();
	~PhysicsActor();

	// delete Function
	PhysicsActor(const PhysicsActor& _Other) = delete;
	PhysicsActor(PhysicsActor&& _Other) noexcept = delete;
	PhysicsActor& operator=(const PhysicsActor& _Other) = delete;
	PhysicsActor& operator=(PhysicsActor&& _Other) noexcept = delete;
protected:
	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 Pos2 = {0,1};
	GameEngineColor CurColor;

	float MaxGravity = 500.0f;
	float JumpForce = 300.0f;

	bool IsJumping;
	bool IsGrounded;
	bool ApplyGravity = true;

	GameEngineColor CalCulateColor(float4 _Pos);
	bool IsFall();
	void RedPixelSnap();
	void BluePixelSnap();
	void GroundCheck();
	void JumpCheck();
	void Jump();
	void Gravity(float _Delta);
	void Update(float _Delta) override;

};

