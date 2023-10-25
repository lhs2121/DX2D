#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatData;
class PlayerStatData;
class MonsterStatData;
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

	void ChangeHp(std::shared_ptr<PlayerStatData> _Stat, float _Damage);
	void ChangeHp(std::shared_ptr<MonsterStatData> _Stat, float _Damage);

	void ChangeExp(float Value);

	static StatManager* Inst;
};