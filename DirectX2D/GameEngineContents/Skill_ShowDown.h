#pragma once
#include "Skill.h"

class Skill_ShowDown : public Skill
{
public:
	// constrcuter destructer
	Skill_ShowDown();
	~Skill_ShowDown();

	// delete Function
	Skill_ShowDown(const Skill_ShowDown& _Other) = delete;
	Skill_ShowDown(Skill_ShowDown&& _Other) noexcept = delete;
	Skill_ShowDown& operator=(const Skill_ShowDown& _Other) = delete;
	Skill_ShowDown& operator=(Skill_ShowDown&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
};

