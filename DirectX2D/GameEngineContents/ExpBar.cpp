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
	ExpGauge->SetImageScale({ 10,10 });
	GameEngineInput::AddInputObject(this);
}

void ExpBar::Update(float _Delta)
{
	if (InputIsPress('Z'))
	{
		ExpGauge->AddImageScale({ 100.0f * _Delta, 0 });
	}
	if (ExpGauge->GetImageTransform().GetLocalScale().X >= 1920)
	{
		int a = 0;
	}
}

void ExpBar::AddExpGauge(float _Value)
{
	//float ConvertValue = _Value * (ContentsCore::GetStartWindowSize().X / maxexp)
	//ExpGauge->AddImageScale({ ConvertValue, 0 });

	if (ExpGauge->GetImageTransform().GetLocalScale().X >= ContentsCore::GetStartWindowSize().X)
	{
		ExpGauge->SetImageScale({ 0,10 });
	}
}
