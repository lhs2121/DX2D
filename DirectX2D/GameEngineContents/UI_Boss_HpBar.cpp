#include "PreCompile.h"
#include "UI_Boss_HpBar.h"

UI_Boss_HpBar::UI_Boss_HpBar()
{
}

UI_Boss_HpBar::~UI_Boss_HpBar()
{
}

void UI_Boss_HpBar::AddHpGauge(float _Value)
{
	if (HpGauge->GetImageTransform().GetLocalScale().X > 0)
	{
		HpGauge->AddImageScale({ _Value ,0 });
	}
	else
	{
		HpGauge->SetImageScale({ 0,0 });
	}
}

void UI_Boss_HpBar::Start()
{
	{
		HpCover = CreateComponent<GameEngineUIRenderer>();
		HpCover->SetRenderOrder(UIRenderOrder::PlayerUI3);
		HpCover->SetSprite("UI_Boss_Vellum_HpGaugeCover.png");
		HpCover->SetPivotType(PivotType::Left);

		HpGauge = CreateComponent<GameEngineUIRenderer>();
		HpGauge->SetRenderOrder(UIRenderOrder::PlayerUI2);
		HpGauge->SetSprite("UI_Boss_Vellum_HpGauge.png");
		HpGauge->SetPivotType(PivotType::LeftBottom);

		HpBG = CreateComponent<GameEngineUIRenderer>();
		HpBG->SetRenderOrder(UIRenderOrder::PlayerUI);
		HpBG->SetSprite("UI_Boss_Vellum_HpGaugeBG.png");
		HpBG->SetPivotType(PivotType::LeftBottom);
		
		Mark = CreateComponent<GameEngineUIRenderer>();
		Mark->SetRenderOrder(UIRenderOrder::PlayerUI3);
		Mark->SetSprite("UI_Boss_Vellum_Mark.png");
		Mark->SetPivotType(PivotType::Right);
		
	}

	float WinSizeY = ContentsCore::GetStartWindowSize().hY();

	{
		float4 CoverScale = HpCover->GetImageTransform().GetLocalScale();
		float4 GaugeScale = HpGauge->GetImageTransform().GetLocalScale();
		float4 MarkScale = Mark->GetImageTransform().GetLocalScale();

		float4 CoverPos = { -CoverScale.hX() ,WinSizeY - CoverScale.hY()};
		HpCover->Transform.SetLocalPosition(CoverPos);

		float4 GaugePos = { -GaugeScale.hX() ,WinSizeY - CoverScale.hY() };
		HpGauge->Transform.SetLocalPosition(CoverPos);
		HpGauge->Transform.AddLocalPosition({ 3,-7 });

		float4 BGPos = { -GaugeScale.hX() ,WinSizeY - CoverScale.hY() };
		HpBG->Transform.SetLocalPosition(CoverPos);
		HpBG->Transform.AddLocalPosition({ 3,-7 });

		float4 MarkPos = { CoverPos.X ,WinSizeY - MarkScale.hY() };
		Mark->Transform.SetLocalPosition(CoverPos);
		Mark->Transform.AddLocalPosition({ 0,-10 });
	}
}

void UI_Boss_HpBar::Update(float _Delta)
{
}
