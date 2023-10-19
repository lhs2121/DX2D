#pragma once
#include "PhysicsActor.h"

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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Hit();
	void Die();

	CollisionOrder EnemyColOrder = CollisionOrder::PlayerWeapon;
	std::shared_ptr<class DamageEffectController> HitDmgEffController;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class MonsterStatData> MonsterStat;
	
};

