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
	void HitByMonster(std::vector<std::shared_ptr<GameEngineCollision>> _Collision);

	float Hp;
	float HitCoolTime;
	std::shared_ptr<class DamageIndicator> DamageRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};

