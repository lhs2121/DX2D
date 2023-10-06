#include "PreCompile.h"
#include "HuntRegion.h"
#include "Player.h"
#include "HuntRegionBG.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"

HuntRegion::HuntRegion()
{
}

HuntRegion::~HuntRegion()
{
}

void HuntRegion::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		Map = CreateActor<HuntRegionBG>(ContentsObjectType::Map);
		CreatePortal("KerningCity", { 1010, -1110 });
	}
}

void HuntRegion::Update(float _Delta)
{
	if (GameEngineInput::IsPress('Q'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,500 * _Delta });
	}
	if (GameEngineInput::IsPress('E'))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0,0,-500 * _Delta });
	}
	if (GameEngineInput::IsDown('C'))
	{
		IsDebug = !IsDebug;
	}
	if (GameEngineInput::IsDown('P'))
	{
		MapleMap::CurMap->SwitchDebugRender();
	}
}

void HuntRegion::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleMap::SetCurMap(Map);
}

void HuntRegion::LevelEnd(GameEngineLevel* _NextLevel)
{

}
