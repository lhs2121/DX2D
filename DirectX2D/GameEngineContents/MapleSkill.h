#pragma once
#include "MapleActor.h"

// Ό³Έν :
class MapleSkill : public MapleActor
{
public:
	// constrcuter destructer
	MapleSkill();
	~MapleSkill();

	// delete Function
	MapleSkill(const MapleSkill& _Other) = delete;
	MapleSkill(MapleSkill&& _Other) noexcept = delete;
	MapleSkill& operator=(const MapleSkill& _Other) = delete;
	MapleSkill& operator=(MapleSkill&& _Other) noexcept = delete;

protected:

};

