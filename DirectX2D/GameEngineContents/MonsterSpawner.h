#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MonsterSpawner : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterSpawner();
	~MonsterSpawner();

	// delete Function
	MonsterSpawner(const MonsterSpawner& _Other) = delete;
	MonsterSpawner(MonsterSpawner&& _Other) noexcept = delete;
	MonsterSpawner& operator=(const MonsterSpawner& _Other) = delete;
	MonsterSpawner& operator=(MonsterSpawner&& _Other) noexcept = delete;

	void Setting(std::string _MonsterString, float _CoolTime, int _SpawnCount, std::vector<float4> _SpawnPoint)
	{
		CurMonsterString = _MonsterString;
		ResetCoolTimeValue = _CoolTime;
		SpawnCount = _SpawnCount;
		SpawnPoint = _SpawnPoint;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;

	std::string CurMonsterString;
	std::vector<float4> SpawnPoint;
	float SpawnCoolTime = 0.0f;
	float ResetCoolTimeValue = 10.0f;
	int SpawnCount;
	int CurMonsterCount = 0;
};

