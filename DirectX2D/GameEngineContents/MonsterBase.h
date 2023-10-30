#pragma once
#include "PhysicsActor.h"

// ���� :
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
	std::shared_ptr<class StatData> GetStat()
	{
		return Stat;
	}
protected:
	void Start() override;
	void Release() override;

	std::string DieAniName;
	std::string HitAniName;
	std::string IdleAniName;
	
	float Hp;
	float HitCoolTime;
	float4 ImageSize;
	std::shared_ptr<class DamageIndicator> DamageRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class StatData> Stat;
};

