#pragma once
#include "MapleLevel.h"

// Ό³Έν :
class HuntLevel : public MapleLevel
{
public:
	// constrcuter destructer
	HuntLevel();
	~HuntLevel();

	// delete Function
	HuntLevel(const HuntLevel& _Other) = delete;
	HuntLevel(HuntLevel&& _Other) noexcept = delete;
	HuntLevel& operator=(const HuntLevel& _Other) = delete;
	HuntLevel& operator=(HuntLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class MapleMap> Map;
};

