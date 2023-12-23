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
	DIE,
	PORTAL,
	FLASHJUMP,
	LUCKYSEVEN,
	SHOWDOWN,
	BOOSTER,
	HASTE
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

	float GetDir() { return Dir; }
	PlayerState GetCurState() { return CurState; }
	std::shared_ptr<class Monster> GetCloseTarget();

	static Player* MainPlayer;
	void PushDamage(std::vector<float> _DamageGroup);
private:
	// Collision
	void MonsterCheck(float _Delta);
	void PortalCheck();
	void ItemCheck();

	// BasicUpdate
	void CameraFocus();
	void RopeCheck();
	void RopePivotUpdate();
	void MoveUpdate();
	void ChangeRandomSwingAnimation();

	// StateUpdate
	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

	// Rope
	void RopeStart();
	void RopeUpdate(float _Delta);

	// Portal
	void PortalStart();

	// Idle
	void IdleUpdate(float _Delta);

	// Walk
	void WalkUpdate(float _Delta);

	// Jump
	void JumpUpdate(float _Delta);

	// Down
	void DownUpdate(float _Delta);

	// Die
	void DieStart();
	void DieUpdate(float _Delta);
	void DieEnd();

	// FlashJump
	void FlashJumpStart();
	void FlashJumpUpdate(float _Delta);

	// LuckySeven
	void LuckySevenStart();
	void LuckySevenUpdate(float _Delta);

	// ShowDown
	void ShowDownStart();
	void ShowDownUpdate(float _Delta);

	// Booster
	void BoosterStart();
	void BoosterUpdate(float _Delta);

	// Haste
	void HasteStart();
	void HasteUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	float Speed = 150.0f;
	float Dir = -1;
	float HitDelay = 0.0f;
	float HitDelayReset = 1.0f;

	bool CanRope = false;
	bool DoubleJump = false;
	bool IsFadeIn = false;

	bool ApplyInput = true;
	bool ApplyInputLeft = true;
	bool ApplyInputRight = true;
	bool ApplyInputJump = true;

	int JumpKey = VK_SPACE;
	int PickUpKey = 'Z';
	int LuckySevenKey = VK_SHIFT;
	int ShowDownKey = VK_CONTROL;
	int BoosterKey = VK_F1;
	int HasteKey = VK_F2;


	float4 RopePos;
	PlayerState CurState;
	std::string PrevLevelName;
};

