#pragma once
#include <GameEngineCore\GameEngineActor.h>

class MonsterStatData :public GameEngineActor
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
	float CurHp = 100.0f;
	float MaxHp = 100.0f;

	float DefRate = 50;
};

class PlayerStatData : public GameEngineActor
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
	float CurHp = 100.0f;
	float MaxHp = 100.0f;

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