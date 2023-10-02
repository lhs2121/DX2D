#include "PreCompile.h"
#include "MapleMap.h"
#include "Player.h"
#include "Portal.h"

std::shared_ptr<MapleMap> MapleMap::CurMap;

MapleMap::MapleMap()
{
}

MapleMap::~MapleMap()
{
}

void MapleMap::SetCurMap(std::shared_ptr<MapleMap> _Map)
{
	CurMap = _Map;
}

float4 MapleMap::GetMapScale()
{
	return MapScale;
}

GameEngineColor MapleMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::string_view a = DebugRenderer->GetCurSprite().Texture->GetName();
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(DebugRenderer->GetCurSprite().Texture->GetName());


	return Tex->GetColor(_Pos, _DefaultColor);
}

std::shared_ptr<class Portal> MapleMap::CreatePortal(std::string _NextLevel, float4 _Pos)
{
	std::shared_ptr<Portal> NewPortal = GetLevel()->CreateActor<Portal>(ContentsObjectType::MapObject);
	std::string Upper = GameEngineString::ToUpperReturn(_NextLevel);
	NewPortal->SetNextMap(Upper);
	NewPortal->Transform.SetWorldPosition(_Pos);
	PortalGroup.insert(std::make_pair(Upper,NewPortal));
	return NewPortal;
}

void MapleMap::SwitchDebugRender()
{
	if(DebugRenderer->IsUpdate() == true)
	{
		DebugRenderer->Off();
	}
	else
	{
		DebugRenderer->On();
	}
	
}

