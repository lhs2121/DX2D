#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class LevelUpEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	LevelUpEffect();
	~LevelUpEffect();

	// delete Function
	LevelUpEffect(const LevelUpEffect& _Other) = delete;
	LevelUpEffect(LevelUpEffect&& _Other) noexcept = delete;
	LevelUpEffect& operator=(const LevelUpEffect& _Other) = delete;
	LevelUpEffect& operator=(LevelUpEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

