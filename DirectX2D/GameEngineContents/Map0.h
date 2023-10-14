#pragma once
#include "MapleMap.h"

// Ό³Έν :
class Map0 : public MapleMap
{
public:
	// constrcuter destructer
	Map0();
	~Map0();

	// delete Function
	Map0(const Map0& _Other) = delete;
	Map0(Map0&& _Other) noexcept = delete;
	Map0& operator=(const Map0& _Other) = delete;
	Map0& operator=(Map0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
};

 