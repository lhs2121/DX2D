#pragma once
#include "MapleSkill.h"
// Ό³Έν :
class LuckySeven : public MapleSkill
{
public:
	static LuckySeven* Inst;
	// constrcuter destructer
	LuckySeven();
	~LuckySeven();

	// delete Function
	LuckySeven(const LuckySeven& _Other) = delete;
	LuckySeven(LuckySeven&& _Other) noexcept = delete;
	LuckySeven& operator=(const LuckySeven& _Other) = delete;
	LuckySeven& operator=(LuckySeven&& _Other) noexcept = delete;

protected:
	float4 GetBulletPos(float _OffSetX = 0, float _OffSetY = 0);
	void Start() override;
	void Update(float _Delta) override;

	float InterTime;
	float CoolTime;
	float MaxCoolTime = 1.3f;
	float MaxInterTime = 0.3f;

	std::shared_ptr<class ProJectile> Sureken1;
	std::shared_ptr<class ProJectile> Sureken2;
};

