#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class ProJectile;
class BulletShooter : public GameEngineActor
{
public:
	// constrcuter destructer
	BulletShooter();
	~BulletShooter();

	// delete Function
	BulletShooter(const BulletShooter& _Other) = delete;
	BulletShooter(BulletShooter&& _Other) noexcept = delete;
	BulletShooter& operator=(const BulletShooter& _Other) = delete;
	BulletShooter& operator=(BulletShooter&& _Other) noexcept = delete;

	static BulletShooter* Inst;

protected:
	float4 GetBulletPos(float4 _OffSet);
	void BulletSetting();
	void Start() override;
	void Update(float _Delta) override;

	bool IsReady = false;

	float InterTime;
	float CoolTime;

	float MaxCoolTime = 0.3f;
	float MaxInterTime = 0.1f;

	float BulletSpeed = 350.0f;
	float BulletCoolTime = 1.0f;

	float4 BulletPosOffset1 = { 5, 30 };
	float4 BulletPosOffset2 = { 7, 20 };

	std::shared_ptr<ProJectile> FirstBullet = nullptr;
	std::shared_ptr<ProJectile> SecondBullet = nullptr;
	std::shared_ptr<ProJectile> Bullet1;
	std::shared_ptr<ProJectile> Bullet2;
	std::shared_ptr<ProJectile> Bullet3;
	std::shared_ptr<ProJectile> Bullet4;
};

