#include "PreCompile.h"
#include "StatusBar.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineUIRenderer.h>

StatusBar::StatusBar()
{
}

StatusBar::~StatusBar()
{
}

void StatusBar::Start()
{
	float4 hSize = ContentsCore::GetStartWindowSize().Half();
	float4 StatusCoverPos;
	{
		StatusCover = CreateComponent<GameEngineUIRenderer>(100);
		StatusCover->Transform.SetLocalPosition({ 0,70 - hSize.Y });
		StatusCover->SetSprite("Status", 3);
		StatusCover->SetRenderOrder(4);
		StatusCoverPos = StatusCover->Transform.GetLocalPosition();
	}

	{
		HpGauge = CreateComponent<GameEngineUIRenderer>(100);
		HpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(10, 0));
		HpGauge->SetSprite("Status", 0);
		HpGauge->SetRenderOrder(3);
	}

	{
		MpGauge = CreateComponent<GameEngineUIRenderer>(100);
		MpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(10, -15));
		MpGauge->SetSprite("Status", 2);
		MpGauge->SetRenderOrder(3);
	}

	{
		LvText = CreateComponent<GameEngineUIRenderer>(100);
		LvText->Transform.SetLocalPosition(StatusCoverPos + float4(-67, 20));
		LvText->SetSprite("Status", 1);

	}
}

void StatusBar::Update(float _Delta)
{
}
