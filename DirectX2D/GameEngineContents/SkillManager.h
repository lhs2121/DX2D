#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Skill;
class SkillManager : public GameEngineActor
{
public:
	// constrcuter destructer
	SkillManager();
	~SkillManager();

	// delete Function
	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;

	void StartSkill(SkillType _Type);

	static SkillManager* Inst;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<class Skill_FlashJump> FlashJump;
	std::shared_ptr<class Skill_ThorwSureken> ThrowSureken;
	std::shared_ptr<class Skill_ShowDown> ShowDown;
};

