#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Sureken;
class SurekenShooter : public GameEngineActor
{
public:
	// constrcuter destructer
	SurekenShooter();
	~SurekenShooter();

	// delete Function
	SurekenShooter(const SurekenShooter& _Other) = delete;
	SurekenShooter(SurekenShooter&& _Other) noexcept = delete;
	SurekenShooter& operator=(const SurekenShooter& _Other) = delete;
	SurekenShooter& operator=(SurekenShooter&& _Other) noexcept = delete;

	static SurekenShooter* Inst;

protected:
	float4 GetSurekenPos(float4 _OffSet);
	void SurekenSetting();
	void Start() override;
	void Update(float _Delta) override;

	bool IsReady = false;

	float InterTime;
	float CoolTime;

	float MaxCoolTime = 0.3f;
	float MaxInterTime = 0.1f;

	float SurekenSpeed = 400.0f;
	float SurekenCoolTime = 1.0f;

	float4 SurekenPosOffset1 = { 5, 30 };
	float4 SurekenPosOffset2 = { 7, 20 };

	std::shared_ptr<Sureken> FirstSureken = nullptr;
	std::shared_ptr<Sureken> SecondSureken = nullptr;
	std::shared_ptr<Sureken> Sureken1;
	std::shared_ptr<Sureken> Sureken2;
	std::shared_ptr<Sureken> Sureken3;
	std::shared_ptr<Sureken> Sureken4;
};

