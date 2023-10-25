#pragma once
#include "DamageActor.h"
// Ό³Έν :
class Sureken : public DamageActor
{
public:
	// constrcuter destructer
	Sureken();
	~Sureken();

	// delete Function
	Sureken(const Sureken& _Other) = delete;
	Sureken(Sureken&& _Other) noexcept = delete;
	Sureken& operator=(const Sureken& _Other) = delete;
	Sureken& operator=(Sureken&& _Other) noexcept = delete;

	void SetDir(float _Dir)
	{
		Dir = _Dir;
	}
	float GetDir()
	{
		return Dir;
	}
	void SetCoolTime(float _CoolTime)
	{
		CoolTime = _CoolTime;
	}
	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}
	void StartFire();
	void Off();
private:
	void Move(float _Delta);
	void StartCoolTime(float _Delta);
	void Start() override;
	void Update(float _Delta) override;

	float Speed;
	float CoolTime;
	float Dir;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

