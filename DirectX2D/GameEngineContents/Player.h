#pragma once
#include "PhysicsActor.h"

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

	float GetDir()
	{
		return dir;
	}

	static Player* MainPlayer;
	std::shared_ptr<class PlayerStatData> GetStat()
	{
		return PlayerStat;
	}
private:
	void FlipRenderer();
	void CameraFocus();
	void DirUpdate();
	void ColCheck(float _Delta);
	void PortalCheck();
	void RopeCheck();
	void RopePivotUpdate();
	void MoveUpdate();
	//basic update

	void RopeStart();
	void HitStart();
	void PortalStart();
	//state start

	void StateUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void RopeUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void HitUpdate(float _Delta);
	//state update

	void FlashJumpStart();
	void LuckySevenStart();
	void ShowDownStart();
	//skill start

	void LuckySevenUpdate(float _Delta);
	void FlashJumpUpdate(float _Delta);
	void ShowDownUpdate(float _Delta);
	//skill update

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

	float Speed = 150.0f;
	float HitCoolTime = 2.0f;
	float dir = -1;

	bool CanHit = true;
	bool CanRope;
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

	float4 RopePos;
	float4 RP;
	PlayerState CurState;
	PlayerDirState CurDirState;
	std::string PrevLevelName;
	std::shared_ptr<GameEngineCollision> Col;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer0;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer1;
	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer2;
	std::shared_ptr<class PlayerStatData> PlayerStat;
};

