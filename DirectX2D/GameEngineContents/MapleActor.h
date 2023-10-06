#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class MapleActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MapleActor();
	~MapleActor();

	// delete Function
	MapleActor(const MapleActor& _Other) = delete;
	MapleActor(MapleActor&& _Other) noexcept = delete;
	MapleActor& operator=(const MapleActor& _Other) = delete;
	MapleActor& operator=(MapleActor&& _Other) noexcept = delete;

	std::shared_ptr<class MapleLevel> GetMapleLevel();
};

