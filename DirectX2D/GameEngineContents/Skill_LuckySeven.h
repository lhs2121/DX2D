#pragma once
#include "Skill.h"

class Skill_LuckySeven : public Skill
{
public:
	// constrcuter destructer
	Skill_LuckySeven();
	~Skill_LuckySeven();

	// delete Function
	Skill_LuckySeven(const Skill_LuckySeven& _Other) = delete;
	Skill_LuckySeven(Skill_LuckySeven&& _Other) noexcept = delete;
	Skill_LuckySeven& operator=(const Skill_LuckySeven& _Other) = delete;
	Skill_LuckySeven& operator=(Skill_LuckySeven&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void StartSkill() override;
	std::shared_ptr<class Projectile> GetNonUpdateProjectile();
	std::shared_ptr<class Projectile> CurProjectile;
	std::list<std::shared_ptr<class Projectile>> ProjectileGroup;
};

