#include "PreCompile.h"
#include "ExpBar.h"

ExpBar* ExpBar::Inst = nullptr;

ExpBar::ExpBar()
{
}

ExpBar::~ExpBar()
{
}

void ExpBar::Start()
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

	int a = ContentsCore::GetStartWindowSize().X;
	std::string SizeX = std::to_string(a);
	ExpCover->SetSprite(SizeX + "ExpCover.png");
	ExpCover2->SetSprite(SizeX +"ExpCover2.png");
	ExpCover3->SetSprite(SizeX +"ExpCover3.png");
	ExpGauge->SetSprite(SizeX + "ExpGauge.png");

	ExpCover->Transform.SetLocalPosition(ExpBarPos);
	ExpCover2->Transform.SetLocalPosition(ExpBarPos);
	ExpCover3->Transform.SetLocalPosition(ExpBarPos);
	ExpGauge->Transform.SetLocalPosition(ExpBarPos);
	ExpGauge->SetImageScale({ 0,10 });

}

void ExpBar::Update(float _Delta)
{

}

void ExpBar::ChangeExpGauge(float _Value)
{
	ExpGauge->AddImageScale({ _Value ,0 });
}

void ExpBar::ExpGaugeReset()
{
	ExpGauge->SetImageScale({ 0,10 });
}

