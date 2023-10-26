#pragma once
#include "PhysicsActor.h"

enum class StatType
{
	Player,
	Monster,
	Boss
};
// Ό³Έν :
class StatData;
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

	void CreateStatData(StatType _Type);
	std::shared_ptr<StatData> GetStatData()
	{
		return MyStatData;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	virtual void Hit();
	virtual void Die();
	void ColCheck();
	void PlayerColUpdate();
	void MonsterColUpdate();

	StatType CurStatType;
	std::shared_ptr<class DamageIndicator> DamageViewer;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<StatData> MyStatData;
};

