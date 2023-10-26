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

	void EffectSetting(float4 _Pos, SkillType _Type, float _Dir);
protected:
	void FlipX(int _dir);
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class DamageActor> SkillDamage;
	std::shared_ptr<class GameEngineCollision> Col;
};

