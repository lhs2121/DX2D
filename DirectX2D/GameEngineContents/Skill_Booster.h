#pragma once
#include "Skill.h"

class Skill_Booster : public Skill
{
public:
	// constrcuter destructer
	Skill_Booster();
	~Skill_Booster();

	// delete Function
	Skill_Booster(const Skill_Booster& _Other) = delete;
	Skill_Booster(Skill_Booster&& _Other) noexcept = delete;
	Skill_Booster& operator=(const Skill_Booster& _Other) = delete;
	Skill_Booster& operator=(Skill_Booster&& _Other) noexcept = delete;

	void StartSkill();
protected:
	void Start() override;
	void Release() override;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

