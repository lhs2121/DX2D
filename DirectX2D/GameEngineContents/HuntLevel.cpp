#include "PreCompile.h"
#include "HuntLevel.h"
#include "Player.h"
#include "HuntingMap.h"
#include "Portal.h"
#include "Monster.h"
#include "MapleMap.h"

HuntLevel::HuntLevel()
{
}

HuntLevel::~HuntLevel()
{
}

void HuntLevel::Start()
{


	GetMainCamera()->Transform.SetLocalPosition({ 0, 0, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		Map = CreateActor<HuntingMap>(ContentsObjectType::Map);
	}

	{
		CreatePortal("KCityLevel", { 310, -1210 });
	}
}

void HuntLevel::Update(float _Delta)
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

void HuntLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	MapleMap::SetCurMap(Map);
}

void HuntLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
