#pragma once
#include "MapleLevel.h"

// ���� :
class KCityLevel : public MapleLevel
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
	std::shared_ptr<class MapleMap> Map;
};

