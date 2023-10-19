#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatData;
class MonsterStatData;
class PlayerStatData;
class DamageActor;
class StatManager : public GameEngineActor
{
public:
	// constrcuter destructer
	StatManager();
	~StatManager();

	// delete Function
	StatManager(const StatManager& _Other) = delete;
	StatManager(StatManager&& _Other) noexcept = delete;
	StatManager& operator=(const StatManager& _Other) = delete;
	StatManager& operator=(StatManager&& _Other) noexcept = delete;

	static StatManager* Inst;

	float GetDamage(GameEngineCollision* _Col);
	void SetDamage(PlayerStatData* _StatData,DamageActor* _Weapon);
	void ChangeHp(MonsterStatData* _StatData, float _HpValue);
	void ChangeHp(PlayerStatData* _StatData,float _HpValue);
	void ChangeMp(PlayerStatData* _StatData,float _MpValue);
	void ChangeExp(PlayerStatData* _StatData,float _ExpValue);
private:
	void Start() override;
	void Update(float _Delta) override;
};