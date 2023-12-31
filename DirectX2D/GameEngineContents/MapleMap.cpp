#include "PreCompile.h"
#include "MapleMap.h"
#include "Player.h"
#include "Portal.h"

MapleMap* MapleMap::CurMap = nullptr;

MapleMap::MapleMap()
{
}

MapleMap::~MapleMap()
{
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
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(DebugRenderer->GetCurSprite().Texture->GetName());

	return Tex->GetColor(_Pos, _DefaultColor);
}

void MapleMap::SwitchDebugRender()
{
	if (DebugRenderer->IsUpdate() == true)
	{
		DebugRenderer->Off();
	}
	else
	{
		DebugRenderer->On();
	}

}

