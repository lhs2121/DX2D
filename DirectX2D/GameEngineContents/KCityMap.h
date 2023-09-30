#pragma once
#include "MapleMap.h"

// Ό³Έν :
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
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 0, 0, 0, 0 });

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
};

 