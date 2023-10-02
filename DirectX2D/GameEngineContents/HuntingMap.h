#pragma once
#include "MapleMap.h"

// Ό³Έν :
class HuntingMap : public MapleMap
{
public:
	// constrcuter destructer
	HuntingMap();
	~HuntingMap();

	// delete Function
	HuntingMap(const HuntingMap& _Other) = delete;
	HuntingMap(HuntingMap&& _Other) noexcept = delete;
	HuntingMap& operator=(const HuntingMap& _Other) = delete;
	HuntingMap& operator=(HuntingMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
	std::shared_ptr<class Portal> Portal0;
};

