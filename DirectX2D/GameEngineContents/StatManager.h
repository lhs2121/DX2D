#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatData;
class StatDataPlayer;
class StatDataMonster;
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

	void ChangeHp(std::shared_ptr<StatDataPlayer> _Stat, float _Damage);
	void ChangeHp(std::shared_ptr<StatDataMonster> _Stat, float _Damage);

	void ChangeExp(float Value);

	static std::shared_ptr<StatManager> Inst;
};