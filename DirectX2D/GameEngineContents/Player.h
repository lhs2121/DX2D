#pragma once
#include "PlayerBase.h"
#include "StatData.h"

enum class PlayerState
{
	IDLE,
	WALK,
	JUMP,
	DOWN,
	ROPE,
	HIT,
	PORTAL,
	FLASHJUMP,
	LUCKYSEVEN,
	SHOWDOWN
};

class GameEngineSpriteRenderer;
class GameEngineCollision;
class Player : public PlayerBase
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

	float GetDir() { return dir; }
	PlayerState GetCurState() { return CurState; }

	static Player* MainPlayer;
private:
	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();
	void PortalCheck();
	void RopeCheck();
	void RopePivotUpdate();
	void MoveUpdate();
	//basic update

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

	void RopeStart();
	void RopeUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);

	void PortalStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DownUpdate(float _Delta);

	void FlashJumpStart();
	void FlashJumpUpdate(float _Delta);

	void LuckySevenStart();
	void LuckySevenUpdate(float _Delta);

	void ShowDownStart();
	void ShowDownUpdate(float _Delta);

	void ShadowPartnerStart();
	void ShadowPartnerUpdate(float _Delta);

	void ChangeRandomSwingAnimation();
	void ChangeDirState(PlayerDirState _State)
	{
		CurDirState = _State;
	}

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	float Speed = 150.0f;
	float dir = -1;

	bool CanHit = true;
	bool CanRope = false;
	bool CanFlip = true;
	bool DirCheck = true;
	bool DoubleJump = false;
	bool IsFadeIn = false;

	bool ApplyInput = true;
	bool ApplyInputLeft = true;
	bool ApplyInputRight = true;
	bool ApplyInputJump = true;

	int JumpKey = VK_MENU;
	int LuckySevenKey = VK_SHIFT;
	int ShowDownKey = VK_CONTROL;

	float4 RopePos;
	PlayerState CurState;
	PlayerDirState CurDirState;
	std::string PrevLevelName;
};

