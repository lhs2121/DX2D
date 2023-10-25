#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DamageActor : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageActor();
	~DamageActor();

	// delete Function
	DamageActor(const DamageActor& _Other) = delete;
	DamageActor(DamageActor&& _Other) noexcept = delete;
	DamageActor& operator=(const DamageActor& _Other) = delete;
	DamageActor& operator=(DamageActor&& _Other) noexcept = delete;

	float GetDamage()
	{
		return Damage;
	}

	void SetDamage(float _Damage)
	{
		Damage = _Damage;
	}
	void SetCollisionScale(float4 _Scale)
	{
		Col->Transform.SetLocalScale(_Scale);
	}
	virtual void Hit();
protected:
	void Start() override;
	
	float Damage;
	std::shared_ptr<class GameEngineCollision> Col;
};

