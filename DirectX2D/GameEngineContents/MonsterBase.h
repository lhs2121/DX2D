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

	void Setting(std::string MonsterName);
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	std::string DieAniName;
	std::string HitAniName;
	std::string IdleAniName;
	
	float hp;
	float4 ImageSize;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};

