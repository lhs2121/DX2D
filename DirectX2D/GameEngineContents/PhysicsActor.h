#pragma once
#include <GameEngineCore\GameEngineActor.h>

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

protected:
	GameEngineColor GetColor(float4 _Pos);
	void SetModuleEnabled(bool _EnableNetForce, bool _EnableCurColor, bool _EnableJumpCheck, bool _EnableGroundCheck,
		bool _EnableGravity, bool _EnableBreaking, bool _EnableBluePixelSnap, bool _EnableRedPixelSnap, bool _EnableLimitToMapBounds);
	void SetCurColor();

	void LimitToMapBounds();
	void GroundCheck();
	void JumpCheck();

	void Gravity(float _Delta);
	void Breaking(float _Delta);
	void RedPixelSnap();
	void BluePixelSnap();

	void Update(float _Delta) override;

	float4 NetForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	GameEngineColor CurColor;

	float BrakingXForce = 1000.0f;
	float BrakingGForce = 1000.0f;
	float MaxGravity = 700.0f;

	bool IsJumping;
	bool IsGrounded;

private:
	bool EnableNetForce = true;
	bool EnableCurColor = true;
	bool EnableJumpCheck = true;
	bool EnableGroundCheck = true;
	bool EnableGravity = true;
	bool EnableBreaking = true;
	bool EnableBluePixelSnap = true;
	bool EnableRedPixelSnap = true;
	bool EnableLimitToMapBounds = true;
};

