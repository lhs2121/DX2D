#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	Projectile();
	~Projectile();

	// delete Function
	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void Setting(float Speed, float Dir, float CoolTime, float CoolTimeReset);
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Off() override;

	float Speed;
	float Dir;
	float CoolTime;
	float CoolTimeReset;
	std::shared_ptr<class GameEngineSpriteRenderer> SurekenRenderer;
	std::shared_ptr<class GameEngineCollision> SurekenCol;
};

