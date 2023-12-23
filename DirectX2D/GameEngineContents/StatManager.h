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

	static std::shared_ptr<StatManager> Inst;

	void AddPlayerStat(std::shared_ptr<class StatDataPlayer> _Stat) { PlayerStat = _Stat; };
	void AddPlayerStatus(std::shared_ptr<class UI_Status> _Status) { PlayerStatus = _Status; };

	void ApplyDamage(float _Damage);

	void ResetHp();
	float GetDamage();
	std::vector<float> GetDamage(int _HitCount, SkillType _Type);

	bool IsDeath();

	void ChangeExp(float Value);

	std::shared_ptr<class StatDataPlayer> PlayerStat;
	std::shared_ptr<class UI_Status> PlayerStatus;
};