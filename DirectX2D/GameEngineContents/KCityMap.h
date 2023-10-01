#pragma once
#include "MapleMap.h"

// ���� :
class KCityMap : public MapleMap
{
public:
	// constrcuter destructer
	KCityMap();
	~KCityMap();

	// delete Function
	KCityMap(const KCityMap& _Other) = delete;
	KCityMap(KCityMap&& _Other) noexcept = delete;
	KCityMap& operator=(const KCityMap& _Other) = delete;
	KCityMap& operator=(KCityMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
	std::shared_ptr<class Portal> Portal0;
};

 