#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class SkillEffect;
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

	void StartSkill(float4 _Pos, SkillType _Type, float dir);

	static SkillManager* Inst;
protected:
	std::shared_ptr<SkillEffect> GetUsableEffect(std::list<std::shared_ptr<SkillEffect>> _list);
	void Start() override;

};

