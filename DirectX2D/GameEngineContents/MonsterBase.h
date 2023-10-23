#pragma once
#include "PhysicsActor.h"

enum class MonsterState
{
	HIT,
	RUN,
	DIE,
};
// Ό³Έν :
class MonsterBase : public PhysicsActor
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

	void HitStart();
	void RunStart();
	void DieStart();

	void HitUpdate(float _Delta);
	void DieUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void ColCheck();

	std::string DieAniName;
	std::string HitAniName;
	std::string RunAniName;
	std::string IdleAniName;
	
	MonsterState CurState = MonsterState::RUN;
	float HitCoolTime = 1.0f;
	float DirCycleTime = 2.0f;
	float Speed = 60.0f;
	int dir = 0;
	float4 ImageSize;
	CollisionOrder EnemyColOrder = CollisionOrder::PlayerWeapon;
	std::shared_ptr<class DamageEffectController> HitDmgEffController;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class GameEngineCollision> TrackingCol;
	std::shared_ptr<class MonsterStatData> MonsterStat;
	
};

