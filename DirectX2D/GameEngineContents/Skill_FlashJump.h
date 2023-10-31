#pragma once
#include "Skill.h"
// Ό³Έν :
class Skill_FlashJump : public Skill
{
public:
	// constrcuter destructer
	Skill_FlashJump();
	~Skill_FlashJump();

	// delete Function
	Skill_FlashJump(const Skill_FlashJump& _Other) = delete;
	Skill_FlashJump(Skill_FlashJump&& _Other) noexcept = delete;
	Skill_FlashJump& operator=(const Skill_FlashJump& _Other) = delete;
	Skill_FlashJump& operator=(Skill_FlashJump&& _Other) noexcept = delete;

	void StartSkill() override;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	std::shared_ptr<class GameEngineSpriteRenderer> GetNonUpdateRenderer();
	std::shared_ptr<class GameEngineSpriteRenderer> CurRenderer;
	std::list<std::shared_ptr<class GameEngineSpriteRenderer>> RendererGroup;
};

