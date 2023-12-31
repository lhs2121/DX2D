#pragma once
#include "MonsterBase.h"
#include "queue"

enum class MonsterState
{
	HIT,
	RUN,
	DIE,
};

// ���� :
class Monster : public MonsterBase
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	void RenderDamage(std::vector<float> _DamageGroup, int _DamageID, int _Order = 0);
	void ApplyDamage(std::vector<float> _DamageGroup);
	void DeathCheck();
	float GetDamage() { return BodyDamage; };
	float4 GetImageSize() { return ImageSize; };

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void DropItem();

	void ChangeState(MonsterState _State);
	void RunStart();
	void RunUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void LevelEnd(GameEngineLevel* _NextLevel) override;

	MonsterState CurState = MonsterState::RUN;
	float HitCoolTime = 0.3f;
	float DirCycleTime = 0.0f;
	float Speed = 60.0f;
	float CurHp = 100.0f;
	float MaxHp = 100.0f;
	float BodyDamage = 500.0f;
	int dir = 0;
};

