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
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
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

