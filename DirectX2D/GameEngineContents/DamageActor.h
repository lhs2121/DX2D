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

	void SetDamage(float _Damage)
	{
		Damage = _Damage;
	}
	float GetDamage()
	{
		return Damage;
	}
protected:
	float Damage;
};

