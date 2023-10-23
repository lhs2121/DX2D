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

	TransformData data = HpGauge->GetImageTransform().GetConstTransformDataRef();
	
	if (data.Scale.X < 0)
	{
		HpGauge->GetImageTransform().SetLocalScale({ 0,HpGaugeSize.Y });
	}
	if (data.Scale.X > HpGaugeSize.X)
	{
		HpGauge->GetImageTransform().SetLocalScale(HpGaugeSize);
	}
}

void StatusBar::ChangeMpGauge(float _Value)
{
	MpGauge->AddImageScale({ _Value,0 });
}

void StatusBar::LevelUp(int Level)
{
	int digit1, digit2, digit3;

	// a의 각 자릿수 추출
	digit1 = Level / 100;    // 백의 자리
	digit2 = (Level % 100) / 10; // 십의 자리
	digit3 = Level % 10;

	LvNumber1->SetSprite("LvNumber", digit1);
	LvNumber2->SetSprite("LvNumber", digit2);
	LvNumber3->SetSprite("LvNumber", digit3);

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
		StatusCover->SetRenderOrder(UIRenderOrder::PlayerUI2);
		StatusCover->SetPivotType(PivotType::Left);
		//StatusCover->Off();
		StatusCoverPos = StatusCover->Transform.GetLocalPosition();
	}

	{
		HpGauge = CreateComponent<GameEngineUIRenderer>(0);
		HpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(25, 0));
		HpGauge->SetSprite("HpGauge.png");
		HpGauge->SetPivotType(PivotType::Left);
		HpGauge->SetRenderOrder(UIRenderOrder::PlayerUI);
	  
		HpGaugeSize = HpGauge->GetImageTransform().GetLocalScale();

	}

	{
		MpGauge = CreateComponent<GameEngineUIRenderer>(0);
		MpGauge->Transform.SetLocalPosition(StatusCoverPos + float4(25, -15));
		MpGauge->SetSprite("MpGauge.png");
		MpGauge->SetPivotType(PivotType::Left);
		MpGauge->SetRenderOrder(UIRenderOrder::PlayerUI);
		MpGaugeSize = HpGauge->GetImageTransform().GetLocalScale();
	}

	{
		LvText = CreateComponent<GameEngineUIRenderer>(1);
		LvText->Transform.SetLocalPosition(StatusCoverPos + float4(32, 22));
		LvText->SetSprite("LvText.png");
		LvText->SetRenderOrder(UIRenderOrder::PlayerUI3);
		LvTextPos = LvText->Transform.GetWorldPosition();

		LvNumber1 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber1->SetRenderOrder(UIRenderOrder::PlayerUI3);

		LvNumber2 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber2->SetRenderOrder(UIRenderOrder::PlayerUI3);

		LvNumber3 = CreateComponent<GameEngineUIRenderer>(1);
		LvNumber3->SetRenderOrder(UIRenderOrder::PlayerUI3);

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
