#include "PreCompile.h"
#include "MapleLevel.h"
#include "Portal.h"

MapleLevel::MapleLevel()
{
}

MapleLevel::~MapleLevel()
{
}

std::shared_ptr<Portal> MapleLevel::CreatePortal(std::string _NextLevel, float4 _Pos)
{
    std::shared_ptr<Portal> NewPortal = CreateActor<Portal>(ActorType::MapObject);
    std::string Upper = GameEngineString::ToUpperReturn(_NextLevel);
    NewPortal->SetNextMap(Upper);
    NewPortal->Transform.SetWorldPosition(_Pos);
    PortalGroup.insert(std::make_pair(Upper, NewPortal));
    return NewPortal;
}

