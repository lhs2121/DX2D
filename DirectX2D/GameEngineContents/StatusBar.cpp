#include "PreCompile.h"
#include "StatusBar.h"
#include <GameEngineCore\GameEngineUIRenderer.h>


StatusBar* StatusBar::Inst = nullptr;

StatusBar::StatusBar()
{
}

StatusBar::~StatusBar()
{
}

void StatusBar::ChangeHpGauge(float _Value)
{
	HpGauge->AddImageScale({ _Value ,0});
}

void StatusBar::ChangeMpGauge(float _Value)
{
	MpGauge->AddImageScale({ _Value,0 });
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
		StatusCover->SetPivotType(PivotType::Left);
		StatusCoverPos = StatusCover->Transform.GetLocalPosition();
	}

	{
		HpGauge = CreateComponent<GameEngineUIRenderer>(0);
		HpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(25, 0));
		HpGauge->SetSprite("HpGauge.png");
		HpGauge->SetPivotType(PivotType::Left);
		HpGauge->SetRenderOrder(0);
		HpGaugeSizeX = HpGauge->GetImageTransform().GetLocalScale().X;

	}

	{
		MpGauge = CreateComponent<GameEngineUIRenderer>(0);
		MpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(25, -15));
		MpGauge->SetSprite("MpGauge.png");
		MpGauge->SetPivotType(PivotType::Left);
		MpGauge->SetRenderOrder(0);
		MpGaugeSizeX = HpGauge->GetImageTransform().GetLocalScale().X;
	}

	{
		LvText = CreateComponent<GameEngineUIRenderer>(1);
		LvText->Transform.SetLocalPosition(StatusCoverPos + float4(32, 22));
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

		LvNumber1->SetSprite("LvNumber", 2);
		LvNumber2->SetSprite("LvNumber", 0);
		LvNumber3->SetSprite("LvNumber", 0);

		LvText->AddImageScale({ -1.0f,0.0f });
		LvNumber1->AddImageScale({ -1.0f,0.0f });
		LvNumber2->AddImageScale({ -1.0f,0.0f });
		LvNumber3->AddImageScale({ -1.0f,0.0f });
	}

}

void StatusBar::Update(float _Delta)
{

}
