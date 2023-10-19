#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatData : public GameEngineActor
{
	friend class StatManager;
public:
	// constrcuter destructer
	StatData();
	~StatData();

	// delete Function
	StatData(const StatData& _Other) = delete;
	StatData(StatData&& _Other) noexcept = delete;
	StatData& operator=(const StatData& _Other) = delete;
	StatData& operator=(StatData&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

protected:
	float CurHp = 30100.0f;
	float MaxHp = 30100.0f;

	float DEF;

private:

};

class MonsterStatData : public StatData
{
	friend class MonsterBase;
	friend class StatManager;
public:
	// constrcuter destructer
	MonsterStatData() {};
	~MonsterStatData() {};

	// delete Function
	MonsterStatData(const MonsterStatData& _Other) = delete;
	MonsterStatData(MonsterStatData&& _Other) noexcept = delete;
	MonsterStatData& operator=(const MonsterStatData& _Other) = delete;
	MonsterStatData& operator=(MonsterStatData&& _Other) noexcept = delete;

private:
	float DefRate = 50;
};

class PlayerStatData : public StatData
{
	friend class Player;
	friend class StatManager;
public:
	// constrcuter destructer
	PlayerStatData() {};
	~PlayerStatData() {};

	// delete Function
	PlayerStatData(const PlayerStatData& _Other) = delete;
	PlayerStatData(PlayerStatData&& _Other) noexcept = delete;
	PlayerStatData& operator=(const PlayerStatData& _Other) = delete;
	PlayerStatData& operator=(PlayerStatData&& _Other) noexcept = delete;

private:
	float CurMp = 100.0f;
	float MaxMp = 100.0f;

	float CurExp = 0.0f;
	float MaxExp = 100.0f;

	int CurLevel = 100;
	int MaxLevel = 300;

	int CurMoney = 0;
	int MaxMoney = 999999999;

	int STR = 10;
	int DEX = 10;
	int INT = 10;
	int LUK = 10;

	int ATK = 10;
	int AtkRate = 0;
	int DmgRate = 0;
	int BossDmgRate = 0;

	float CriDmg = 50;
	float CriRate = 50;

};