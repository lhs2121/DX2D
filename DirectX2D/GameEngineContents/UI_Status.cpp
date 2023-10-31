#include "PreCompile.h"
#include "UI_Status.h"
#include <GameEngineCore\GameEngineUIRenderer.h>


UI_Status* UI_Status::Inst = nullptr;

UI_Status::UI_Status()
{
}

UI_Status::~UI_Status()
{
}

void UI_Status::ChangeHpGauge(float _Value)
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

void UI_Status::ResetHpGauge()
{
}

void UI_Status::ChangeMpGauge(float _Value)
{
	MpGauge->AddImageScale({ _Value,0 });
}

void UI_Status::ResetMpGauge()
{
}

void UI_Status::ChangeExpGauge(float _Value)
{
	ExpGauge->AddImageScale({ _Value ,0 });

	TransformData data = ExpGauge->GetImageTransform().GetConstTransformDataRef();

	if (data.Scale.X > ContentsCore::GetStartWindowSize().X)
	{
		ResetExpGauge();
	}
}

void UI_Status::ResetExpGauge()
{
	ExpGauge->SetImageScale({ 0,10 });
}
void UI_Status::LevelUp(int Level)
{
	int digit1, digit2, digit3;

	digit1 = Level / 100;    
	digit2 = (Level % 100) / 10;
	digit3 = Level % 10;

	LvNumber1->SetSprite("LvNumber", digit1);
	LvNumber2->SetSprite("LvNumber", digit2);
	LvNumber3->SetSprite("LvNumber", digit3);

}

void UI_Status::Start()
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

		LvNumber1->SetSprite("LvNumber", 1);
		LvNumber2->SetSprite("LvNumber", 0);
		LvNumber3->SetSprite("LvNumber", 0);

		LvText->AddImageScale({ -1.0f,0.0f });
		LvNumber1->AddImageScale({ -1.0f,0.0f });
		LvNumber2->AddImageScale({ -1.0f,0.0f });
		LvNumber3->AddImageScale({ -1.0f,0.0f });
	}

	{
		float4 hSize = ContentsCore::GetStartWindowSize().Half();
		float4 ExpBarPos = { -hSize.X,-hSize.Y + 5.0f };

		ExpCover = CreateComponent<GameEngineUIRenderer>(0);
		ExpCover->SetRenderOrder(UIRenderOrder::PlayerUI);
		ExpCover->SetPivotType(PivotType::Left);

		ExpGauge = CreateComponent<GameEngineUIRenderer>(0);
		ExpGauge->SetRenderOrder(UIRenderOrder::PlayerUI2);
		ExpGauge->SetPivotType(PivotType::Left);

		ExpCover2 = CreateComponent<GameEngineUIRenderer>(0);
		ExpCover2->SetRenderOrder(UIRenderOrder::PlayerUI3);
		ExpCover2->SetPivotType(PivotType::Left);

		ExpCover3 = CreateComponent<GameEngineUIRenderer>(0);
		ExpCover3->SetRenderOrder(UIRenderOrder::PlayerUI3);
		ExpCover3->SetPivotType(PivotType::Left);

		int WinSizeX = ContentsCore::GetStartWindowSize().iX();
		std::string StringX = std::to_string(WinSizeX);
		ExpCover->SetSprite(StringX + "ExpCover.png");
		ExpCover2->SetSprite(StringX + "ExpCover2.png");
		ExpCover3->SetSprite(StringX + "ExpCover3.png");
		ExpGauge->SetSprite(StringX + "ExpGauge.png");

		ExpCover->Transform.SetLocalPosition(ExpBarPos);
		ExpCover2->Transform.SetLocalPosition(ExpBarPos);
		ExpCover3->Transform.SetLocalPosition(ExpBarPos);
		ExpGauge->Transform.SetLocalPosition(ExpBarPos);
		ExpGauge->Transform.AddLocalPosition({ 15.0f,0 });
		ExpGauge->SetImageScale({ 30,10 });
	}
}

void UI_Status::Update(float _Delta)
{

}
