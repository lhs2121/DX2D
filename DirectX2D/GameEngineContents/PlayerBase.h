#pragma once
#include "PhysicsActor.h"

// Ό³Έν :
class PlayerBase : public PhysicsActor
{
public:
	// constrcuter destructer
	PlayerBase();
	~PlayerBase();

	// delete Function
	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(PlayerBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	float4 ImageSize;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};

