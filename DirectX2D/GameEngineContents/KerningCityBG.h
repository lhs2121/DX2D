#pragma once
#include "MapleMap.h"

// Ό³Έν :
class KerningCityBG : public MapleMap
{
public:
	// constrcuter destructer
	KerningCityBG();
	~KerningCityBG();

	// delete Function
	KerningCityBG(const KerningCityBG& _Other) = delete;
	KerningCityBG(KerningCityBG&& _Other) noexcept = delete;
	KerningCityBG& operator=(const KerningCityBG& _Other) = delete;
	KerningCityBG& operator=(KerningCityBG&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
};

 