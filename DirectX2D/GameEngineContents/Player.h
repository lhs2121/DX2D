#pragma once
#include "PhysicsActor.h"

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

	float GetDir()
	{
		switch (CurDirState)
		{
		case PlayerDirState::LEFT:
			return -1;
		case PlayerDirState::RIGHT:
			return 1;
		}
	}

	static Player* MainPlayer;

private:
	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();
	//basic

	void ColCheck();
	void PortalCheck();
	//colcheck

	void RopeCheck();
	void RopePivotUpdate();
	//rope

	void StateUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void MeleeAttackUpdate(float _Delta);
	void AutoAttackUpdate(float _Delta);
	void LuckySevenUpdate(float _Delta);
	//state

	void ChangeRandomSwingAnimation();
	void ChangeDirState(PlayerDirState _State)
	{
		CurDirState = _State;
	}
	void ChangeState(PlayerState _State);

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	PlayerState CurState;
	PlayerDirState CurDirState;
	float Speed = 125;
	float4 RopePos;
	bool CanRope;
	bool CanFlip = true;
	std::string PrevLevelName;

	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer0;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer1;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer2;
	std::shared_ptr<GameEngineCollision> Col;
};

