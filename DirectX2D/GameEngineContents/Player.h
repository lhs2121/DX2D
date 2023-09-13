#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
class Player : public GameEngineActor
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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	float4 GrivityForce = {0.0f, 0.0f, 0.0f, 1.0f};
	float speed = 500;

	PlayerState CurState;
	PlayerDirState CurDirState = PlayerDirState::LEFT;

	void StateCheck();
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
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AttackUpdate(float _Delta);
};

