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
	float4 LvTextPos;
	{
		StatusCover = CreateComponent<GameEngineUIRenderer>(0);
		StatusCover->Transform.SetLocalPosition({ 0,70 - hSize.Y });
		StatusCover->SetSprite("StatusCover.png");
		StatusCover->SetRenderOrder(1);
		StatusCoverPos = StatusCover->Transform.GetLocalPosition();
	}

	{
		HpGauge = CreateComponent<GameEngineUIRenderer>(0);
		HpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(10, 0));
		HpGauge->SetSprite("HpGauge.png");
		HpGauge->SetRenderOrder(0);
	}

	{
		MpGauge = CreateComponent<GameEngineUIRenderer>(0);
		MpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(10, -15));
		MpGauge->SetSprite("MpGauge.png");
		MpGauge->SetRenderOrder(0);
	}

	{
		LvText = CreateComponent<GameEngineUIRenderer>(1);
		LvText->Transform.SetLocalPosition(StatusCoverPos + float4(-67, 22));
		LvText->SetSprite("LvText.png");
		LvText->SetRenderOrder(2);
		LvTextPos = LvText->Transform.GetWorldPosition();

		LvNumber1 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber1->SetRenderOrder(2);

		LvNumber2 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber2->SetRenderOrder(2);

		LvNumber3 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber3->SetRenderOrder(2);

		LvNumber1->Transform.SetLocalPosition(LvTextPos + float4(14, 0));
		LvNumber2->Transform.SetLocalPosition(LvTextPos + float4(21, 0));
		LvNumber3->Transform.SetLocalPosition(LvTextPos + float4(28, 0));

		LvNumber1->SetSprite("LvNumber", 1);
		LvNumber2->SetSprite("LvNumber", 3);
		LvNumber3->SetSprite("LvNumber", 9);

		LvText->AddImageScale({ -1.0f,0.0f });
		LvNumber1->AddImageScale({ -1.0f,0.0f });
		LvNumber2->AddImageScale({ -1.0f,0.0f });
		LvNumber3->AddImageScale({ -1.0f,0.0f });
	}

	{
		float4 ExpBarPos = { 0,-hSize.Y + 5.0f };
	
	/*	ExpBG = CreateComponent<GameEngineUIRenderer>(2);
		ExpBG->Transform.SetLocalPosition(ExpBarPos);
		ExpBG->SetSprite("ExpBar", 0);
		ExpBG->SetRenderOrder(3);*/

		ExpCover = CreateComponent<GameEngineUIRenderer>(2);
		ExpCover->Transform.SetLocalPosition(ExpBarPos);
		ExpCover->SetSprite("ExpCover.png");
		ExpCover->SetRenderOrder(1);

		ExpGauge = CreateComponent<GameEngineUIRenderer>(2);
		ExpGauge->Transform.SetLocalPosition(ExpBarPos);
		ExpGauge->SetSprite("ExpGauge.png");
		ExpGauge->SetRenderOrder(2);

		ExpCover2 = CreateComponent<GameEngineUIRenderer>(2);
		ExpCover2->Transform.SetLocalPosition(ExpBarPos);
		ExpCover2->SetSprite("ExpCover2.png");
		ExpCover2->SetRenderOrder(3);

		// ExpNumber;
	}

}

void StatusBar::Update(float _Delta)
{
}
