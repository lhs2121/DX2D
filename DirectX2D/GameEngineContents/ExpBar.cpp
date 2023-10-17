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
	ExpCover->SetSprite("ExpCover.png");
	ExpCover->SetRenderOrder(1);
	ExpCover->SetPivotType(PivotType::Left);

	ExpGauge = CreateComponent<GameEngineUIRenderer>(0);
	ExpGauge->SetSprite("ExpGauge.png");
	ExpGauge->SetRenderOrder(2);
	ExpGauge->SetPivotType(PivotType::Left);

	ExpCover2 = CreateComponent<GameEngineUIRenderer>(0);
	ExpCover2->SetSprite("ExpCover2.png");
	ExpCover2->SetRenderOrder(3);
	ExpCover2->SetPivotType(PivotType::Left);

	ExpCover3 = CreateComponent<GameEngineUIRenderer>(0);
	ExpCover3->SetSprite("ExpCover3.png");
	ExpCover3->SetRenderOrder(4);
	ExpCover3->SetPivotType(PivotType::Left);


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
