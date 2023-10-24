#pragma once
#include "MapleMap.h"

// Ό³Έν :
class Map2 : public MapleMap
{
public:
	// constrcuter destructer
	Map2();
	~Map2();

	// delete Function
	Map2(const Map2& _Other) = delete;
	Map2(Map2&& _Other) noexcept = delete;
	Map2& operator=(const Map2& _Other) = delete;
	Map2& operator=(Map2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;
};

