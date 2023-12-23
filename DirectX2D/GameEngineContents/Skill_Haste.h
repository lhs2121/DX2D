#pragma once
#include "Skill.h"

class Skill_Haste : public Skill
{
public:
	// constrcuter destructer
	Skill_Haste();
	~Skill_Haste();

	// delete Function
	Skill_Haste(const Skill_Haste& _Other) = delete;
	Skill_Haste(Skill_Haste&& _Other) noexcept = delete;
	Skill_Haste& operator=(const Skill_Haste& _Other) = delete;
	Skill_Haste& operator=(Skill_Haste&& _Other) noexcept = delete;

	void StartSkill();
protected:
	void Start() override;
	void Release() override;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

