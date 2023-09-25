#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PhysicsActor : public GameEngineActor
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

	void SetPos(float4 _Bottom1, float4 _Bottom2);
protected:
	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 Pos1 = {0,0};
	float4 Pos2 = {0,1};
	float4 Pos3;
	GameEngineColor CurColor;

	float MaxGravity = 300.0f;
	float JumpForce = 300.0f;

	bool IsJumping;
	bool IsGrounded;
	bool CanClimbRope; 

	bool IsFall();
	void RedPixelSnap();
	void BluePixelSnap();
	void GroundCheck();
	void JumpCheck();
	void Jump();
	void Gravity(float _Delta);
	void Update(float _Delta) override;

};

