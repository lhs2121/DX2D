#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class KCityLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	KCityLevel();
	~KCityLevel();

	// delete Function
	KCityLevel(const KCityLevel& _Other) = delete;
	KCityLevel(KCityLevel&& _Other) noexcept = delete;
	KCityLevel& operator=(const KCityLevel& _Other) = delete;
	KCityLevel& operator=(KCityLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

