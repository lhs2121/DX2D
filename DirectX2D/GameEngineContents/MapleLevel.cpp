#include "PreCompile.h"
#include "MapleLevel.h"

MapleLevel::MapleLevel()
{
}

MapleLevel::~MapleLevel()
{
}

bool MapleLevel::FindActor(int num)
{
    if (Childs.find(num) != Childs.end()) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void MapleLevel::EraseActor()
{
    Childs.erase(1);
}

void MapleLevel::InsertActor()
{

}
