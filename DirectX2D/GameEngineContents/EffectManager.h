#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class EffectManager : public GameEngineActor
{
public:
	// constrcuter destructer
	EffectManager();
	~EffectManager();

	// delete Function
	EffectManager(const EffectManager& _Other) = delete;
	EffectManager(EffectManager&& _Other) noexcept = delete;
	EffectManager& operator=(const EffectManager& _Other) = delete;
	EffectManager& operator=(EffectManager&& _Other) noexcept = delete;

	static EffectManager* Inst;

	void StartEffect(float4 _Pos,SkillType _Type);
protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

