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
		return dir;
	}

	static Player* MainPlayer;

private:
	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();
	//basic

	void ColCheck();
	void PortalCheck();
	//col

	void RopeCheck();
	void RopePivotUpdate();
	//rope

	void RopeStart();
	//start

	void MoveUpdate();
	//move

	void FlashJumpStart();
	void LuckySevenStart();

	//state start
	void StateUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void MeleeAttackUpdate(float _Delta);
	void AutoAttackUpdate(float _Delta);
	void LuckySevenUpdate(float _Delta);
	void FlashJumpUpdate(float _Delta);
	//state update

	void ChangeRandomSwingAnimation();
	void ChangeDirState(PlayerDirState _State)
	{
		CurDirState = _State;
	}
	void ChangeState(PlayerState _State);

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	
	float Speed = 125;
	float dir;
	bool CanRope;
	bool CanFlip = true;
	bool DirCheck = true;
	bool DoubleJump = false;

	bool ApplyInput = true;
	bool ApplyInputLeft = true;
	bool ApplyInputRight = true;
	bool ApplyInputJump = true;

	int JumpKey = VK_MENU;
	int LuckySevenKey = VK_SHIFT;

	float4 RopePos;
	PlayerState CurState;
	PlayerDirState CurDirState;
	std::string PrevLevelName;
	std::shared_ptr<GameEngineCollision> Col;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer0;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer1;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer2;
};

