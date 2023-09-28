#pragma once
#include "PhysicsActor.h"

enum class PlayerState
{
	IDLE,
	RUN,
	DOWN,
	ROPE,
	ATTACK,
};
enum class PlayerDirState
{
	LEFT,
	RIGHT,
};


class GameEngineSpriteRenderer;
class GameEngineCollision;
class Player : public PhysicsActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:
	float4 RopePos;
	PlayerState CurState;
	PlayerDirState CurDirState;
	float Speed = 125;
	bool CanRope;

	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer0;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer1;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer2;
	std::shared_ptr<GameEngineCollision> Col;

	void ChangeState(PlayerState _State);
	void ChangeDirState(PlayerDirState _State)
	{
		CurDirState = _State;
	}

	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();
	void HitUpdate();
	void PortalCheck();

	void RopeCheck();
	void RopePivotUpdate();

	void StateUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AttackUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
};

