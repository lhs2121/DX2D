#include "PreCompile.h"
#include "MapleActor.h"
#include "Portal.h"
#include "MapleLevel.h"

MapleActor::MapleActor()
{
}

MapleActor::~MapleActor()
{
}

std::shared_ptr<MapleLevel> MapleActor::GetMapleLevel()
{
	return GetLevel()->GetDynamic_Cast_This<MapleLevel>();
}
