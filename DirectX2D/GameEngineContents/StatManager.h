#pragma once
#include <GameEngineCore\GameEngineActor.h>

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

	void ChangeHp(float _HpValue);
	void ChangeMp(float _MpValue);
	void ChangeExp(float _ExpValue);
private:
	void Start() override;
	void Update(float _Delta) override;

	

	std::shared_ptr<class Player> Player;
	std::shared_ptr<class PlayerStat> Stat;
	std::shared_ptr<class StatusBar> StatusBar;
	std::shared_ptr<class ExpBar> ExpBar;

};