#pragma once
#include "CombatActor.h"

enum class MonsterState
{
	HIT,
	RUN,
	DIE,
};
// Ό³Έν :
class MonsterBase : public CombatActor
{
public:
	// constrcuter destructer
	MonsterBase();
	~MonsterBase();

	// delete Function
	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

	void Setting(std::string MonsterName);
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void ChangeState(MonsterState _State);


	void RunStart();
	void RunUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void Hit() override;
    void Die() override;

	std::string DieAniName;
	std::string HitAniName;
	std::string IdleAniName;
	
	MonsterState CurState = MonsterState::RUN;
	float HitCoolTime = 0.3f;
	float DirCycleTime = 0.0f;
	float Speed = 60.0f;
	int dir = 0;
	float4 ImageSize;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

