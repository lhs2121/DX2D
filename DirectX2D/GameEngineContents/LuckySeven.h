#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
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

protected:
	float InterTime;

	bool DoneFire1 = false;
	bool DoneFire2 = false;

	std::shared_ptr<class ProJectile> sureken1;
	std::shared_ptr<class ProJectile> sureken2;

	float4 GetBulletPos();
	void Start() override;
	void Update(float _Delta) override;
};

