#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatData : public GameEngineActor
{
	friend class StatManager;
public:
	// constrcuter destructer
	StatData() {};
	~StatData() {};

	// delete Function
	StatData(const StatData& _Other) = delete;
	StatData(StatData&& _Other) noexcept = delete;
	StatData& operator=(const StatData& _Other) = delete;
	StatData& operator=(StatData&& _Other) noexcept = delete;

	virtual float GetDamage();
	virtual std::vector<float> GetDamage(int _HitCount);

	int CurLevel = 100;
	int MaxLevel = 300;

	float CurHp = 100.0f;
	float MaxHp = 100.0f;

	float DEF = 10.0f;
};

class StatDataMonster : public StatData
{
	friend class StatManager;
public:
	// constrcuter destructer
	StatDataMonster() {};
	~StatDataMonster() {};

	// delete Function
	StatDataMonster(const StatDataMonster& _Other) = delete;
	StatDataMonster(StatDataMonster&& _Other) noexcept = delete;
	StatDataMonster& operator=(const StatDataMonster& _Other) = delete;
	StatDataMonster& operator=(StatDataMonster&& _Other) noexcept = delete;

private:
	float GetDamage() override;

	float BodyDamage = 50.0f;
	float DefRate = 10;
};

class StatDataPlayer : public StatData
{
	friend class StatManager;
public:
	// constrcuter destructer
	StatDataPlayer() {};
	~StatDataPlayer() {};

	// delete Function
	StatDataPlayer(const StatDataPlayer& _Other);
	StatDataPlayer(StatDataPlayer&& _Other) noexcept = delete;
	StatDataPlayer& operator=(const StatDataPlayer& _Other) = delete;
	StatDataPlayer& operator=(StatDataPlayer&& _Other) noexcept = delete;

private:
	float GetDamage() override;
	std::vector<float> GetDamage(int _HitCount) override;

	float CurMp = 100.0f;
	float MaxMp = 100.0f;

	float CurExp = 0.0f;
	float MaxExp = 100.0f;

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