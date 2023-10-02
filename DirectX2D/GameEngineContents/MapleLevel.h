#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MapleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MapleLevel();
	~MapleLevel();

	// delete Function
	MapleLevel(const MapleLevel& _Other) = delete;
	MapleLevel(MapleLevel&& _Other) noexcept = delete;
	MapleLevel& operator=(const MapleLevel& _Other) = delete;
	MapleLevel& operator=(MapleLevel&& _Other) noexcept = delete;

	bool FindActor(int num);
	void EraseActor();
	void InsertActor();
};

