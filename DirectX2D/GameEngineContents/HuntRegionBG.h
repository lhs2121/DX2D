#pragma once
#include "MapleMap.h"

// Ό³Έν :
class HuntRegionBG : public MapleMap
{
public:
	// constrcuter destructer
	HuntRegionBG();
	~HuntRegionBG();

	// delete Function
	HuntRegionBG(const HuntRegionBG& _Other) = delete;
	HuntRegionBG(HuntRegionBG&& _Other) noexcept = delete;
	HuntRegionBG& operator=(const HuntRegionBG& _Other) = delete;
	HuntRegionBG& operator=(HuntRegionBG&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
};

