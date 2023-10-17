#pragma once
#include <GameEngineCore\GameEngineActor.h>

class PlayerStat : public GameEngineActor
{
	friend class StatManager;
public:
	// constrcuter destructer
	PlayerStat();
	~PlayerStat();

	// delete Function
	PlayerStat(const PlayerStat& _Other) = delete;
	PlayerStat(PlayerStat&& _Other) noexcept = delete;
	PlayerStat& operator=(const PlayerStat& _Other) = delete;
	PlayerStat& operator=(PlayerStat&& _Other) noexcept = delete;

	static PlayerStat* Inst;

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	float CurHp = 100.0f;
	float MaxHp = 100.0f;

	float CurMp = 100.0f;
	float MaxMp = 100.0f;

	float CurExp = 100.0f;
	float MaxExp = 100.0f;

	int CurLevel = 100;
	int MaxLevel = 300;

	int CurMoney = 0;
	int MaxMoney = 999999999;
};