#pragma once
#include "PhysicsActor.h"

// Ό³Έν :
class CombatActor : public PhysicsActor
{
public:
	// constrcuter destructer
	CombatActor();
	~CombatActor();

	// delete Function
	CombatActor(const CombatActor& _Other) = delete;
	CombatActor(CombatActor&& _Other) noexcept = delete;
	CombatActor& operator=(const CombatActor& _Other) = delete;
	CombatActor& operator=(CombatActor&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _Delta) override;

	void SetEnemyOrder(CollisionOrder _Order)
	{
		EnemyColOrder = _Order;
	}

	float hp = 100;
	CollisionOrder EnemyColOrder;
	std::shared_ptr<class DamageEffectController> HitDmgEffController;
	std::shared_ptr<class GameEngineCollision> Col;
};

