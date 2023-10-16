#pragma once
#include "MapleLevel.h"

// Ό³Έν :
class HuntRegion : public MapleLevel
{
public:
	// constrcuter destructer
	HuntRegion();
	~HuntRegion();

	// delete Function
	HuntRegion(const HuntRegion& _Other) = delete;
	HuntRegion(HuntRegion&& _Other) noexcept = delete;
	HuntRegion& operator=(const HuntRegion& _Other) = delete;
	HuntRegion& operator=(HuntRegion&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

};

