#pragma once
#include "Skill.h"

class Skill_ThorwSureken : public Skill
{
public:
	// constrcuter destructer
	Skill_ThorwSureken();
	~Skill_ThorwSureken();

	// delete Function
	Skill_ThorwSureken(const Skill_ThorwSureken& _Other) = delete;
	Skill_ThorwSureken(Skill_ThorwSureken&& _Other) noexcept = delete;
	Skill_ThorwSureken& operator=(const Skill_ThorwSureken& _Other) = delete;
	Skill_ThorwSureken& operator=(Skill_ThorwSureken&& _Other) noexcept = delete;

	void StartSkill();
	void SetThrowCount(int _Count) { ThrowCount = _Count; };
protected:
	void Start() override;
	void Release() override;

	int ThrowCount;
	std::shared_ptr<class Projectile> GetNonUpdateProjectile();
	std::shared_ptr<class Projectile> CurProjectile;
	std::shared_ptr<class GameEngineCollision> MonsterDetector;
	std::list<std::shared_ptr<class Projectile>> ProjectileGroup;
};

