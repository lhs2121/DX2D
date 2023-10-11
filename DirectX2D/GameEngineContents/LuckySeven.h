#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class ProJectile;
class LuckySeven : public GameEngineActor
{
public:
	// constrcuter destructer
	LuckySeven();
	~LuckySeven();

	// delete Function
	LuckySeven(const LuckySeven& _Other) = delete;
	LuckySeven(LuckySeven&& _Other) noexcept = delete;
	LuckySeven& operator=(const LuckySeven& _Other) = delete;
	LuckySeven& operator=(LuckySeven&& _Other) noexcept = delete;

	static LuckySeven* Inst;

protected:
	float4 GetBulletPos(float4 _OffSet);
	void Start() override;
	void Update(float _Delta) override;
	void BulletSetting();

	float InterTime;
	float CoolTime;

	float MaxCoolTime = 0.5f;
	float MaxInterTime = 0.1f;

	float BulletSpeed = 400.0f;
	float BulletCoolTime = 1.0f;

	float4 	BulletPosOffset1 = { 5, 30 };
	float4 	BulletPosOffset2 = { 7, 20 };

	bool IsJoinUpdate = true;
	std::shared_ptr<ProJectile> FirstBullet = nullptr;
	std::shared_ptr<ProJectile> SecondBullet = nullptr;
	std::shared_ptr<ProJectile> Bullet1;
	std::shared_ptr<ProJectile> Bullet2;
	std::shared_ptr<ProJectile> Bullet3;
	std::shared_ptr<ProJectile> Bullet4;
};

