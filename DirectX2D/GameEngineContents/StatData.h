#pragma once
#include <GameEngineCore\GameEngineActor.h>

class StatDataPlayer : public GameEngineActor
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

	int CurLevel = 100;
	int MaxLevel = 300;
	float DEF = 10.0f;

	float CurHp = 100000.0f;
	float MaxHp = 100000.0f;

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
	int AtkRate = 10;
	int DmgRate = 10;
	int BossDmgRate = 10;

	float CriDmg = 10;
	float CriRate = 10;

	float LuckySevenRate = 540.0f;
	float ShowDownRate = 708.0f;

};