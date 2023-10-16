#pragma once
#include <GameEngineCore\GameEngineActor.h>

class PlayerStat : public GameEngineActor
{
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

	float curhp = 100.0f;
	float maxhp = 100.0f;

	float curmp = 100.0f;
	float maxmp = 100.0f;

	float curexp = 100.0f;
	float maxexp = 100.0f;

	int level = 100;
	int maxlevel = 300;

	int money = 0;
	int maxmoney = 999999999;
};