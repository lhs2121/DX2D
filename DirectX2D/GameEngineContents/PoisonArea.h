#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PoisonArea : public GameEngineActor
{
public:
	// constrcuter destructer
	PoisonArea();
	~PoisonArea();

	// delete Function
	PoisonArea(const PoisonArea& _Other) = delete;
	PoisonArea(PoisonArea&& _Other) noexcept = delete;
	PoisonArea& operator=(const PoisonArea& _Other) = delete;
	PoisonArea& operator=(PoisonArea&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	float CoolTime = 5.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};