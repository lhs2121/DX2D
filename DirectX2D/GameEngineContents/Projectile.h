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

	void Setting(float4 _Pos, float _Speed, float _Dir, float _CoolTime, float StartDelayTime);
	void SetDamage(std::vector<float> _DamageGroup, int _DamageID);
protected:
	void Start() override;
	void Update(float _Delta) override;
	void On() override;

	float Speed;
	float Dir;
	float CoolTime;
	float CoolTimeReset;
	float StartDelayTime;
	int DamageID;
	bool CanHitMonster = true;

	std::vector<float> DamageGroup;
	std::shared_ptr<class GameEngineSpriteRenderer> SurekenRenderer;
	std::shared_ptr<class GameEngineCollision> SurekenCol;
};

