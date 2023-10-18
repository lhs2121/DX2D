#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class SkillEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	SkillEffect();
	~SkillEffect();

	// delete Function
	SkillEffect(const SkillEffect& _Other) = delete;
	SkillEffect(SkillEffect&& _Other) noexcept = delete;
	SkillEffect& operator=(const SkillEffect& _Other) = delete;
	SkillEffect& operator=(SkillEffect&& _Other) noexcept = delete;


	void ChangeAnimation(std::string _String);
	void FlipX(int _dir);
protected:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

