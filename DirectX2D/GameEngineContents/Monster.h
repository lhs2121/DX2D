#pragma once
#include "PhysicsActor.h"

// Ό³Έν :
class Monster : public PhysicsActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;
	std::shared_ptr<class GameEngineCollision> Col;
protected:

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderer;
};

