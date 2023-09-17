#pragma once
#include "PhysicsActor.h"

enum class PlayerState
{
	IDLE,
	RUN,
	ROPE,
	DOWN,
	JUMP,
	ATTACK,
};
enum class PlayerDirState
{
	LEFT,
	RIGHT,
	ROPE,
	DOWN,
};

// Ό³Έν :
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
	float4 FootPos1 = { 0 , -43.5f };
	float4 FootPos2 = { 0 , -42.5f };

    float Speed = 150;
	float JumpForce = 450.0f;
	bool CanJump = false;

	PlayerState CurState = PlayerState::IDLE;
	PlayerDirState CurDirState = PlayerDirState::LEFT;

    std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer1;




	void ChangeState(PlayerState _State)
	{
		CurState = _State;
	}
	void ChangeDirState(PlayerDirState _State)
	{
		CurDirState = _State;
	}
	
	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();

	void GravityUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AttackUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
};

