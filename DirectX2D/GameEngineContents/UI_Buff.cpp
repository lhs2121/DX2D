#include "PreCompile.h"
#include "UI_Buff.h"
#include "StatData.h"
#include "StatManager.h"


std::shared_ptr<UI_Buff> UI_Buff::Inst = nullptr;

UI_Buff::UI_Buff()
{
}

UI_Buff::~UI_Buff()
{
}

void UI_Buff::RenderBuffUI(SkillType _Type)
{
	std::string SpriteName;
	switch (_Type)
	{
	case SkillType::SurekenBooster:
		SpriteName = "BoosterIcon.png";
		break;
	case SkillType::Haste:
		SpriteName = "HasteIcon.png";
		break;
	default:
		break;
	}

	for (size_t i = 0; i < 5; i++)
	{
		if (RendererGroup[i]->IsUpdate() == false)
		{
			RendererGroup[i]->SetSprite(SpriteName);
			float4 Scale = RendererGroup[0]->GetImageTransform().GetLocalScale();
			RendererGroup[i]->Transform.AddLocalPosition({ -Scale.X * i,0 });
			RendererGroup[i]->On();

			break;
		}
	}
}

void UI_Buff::Start()
{
	RendererGroup.reserve(5);
	float4 WinSize = ContentsCore::GetStartWindowSize();
	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr<GameEngineUIRenderer> NewRenderer = CreateComponent<GameEngineUIRenderer>(0);
		NewRenderer->AutoSpriteSizeOn();
		NewRenderer->SetSprite("BoosterIcon.png");
		float4 Scale = NewRenderer->GetImageTransform().GetLocalScale();
		NewRenderer->Transform.SetLocalPosition(WinSize.Half());
		NewRenderer->Transform.AddLocalPosition({ -Scale.hX(),-Scale.hY() });
		NewRenderer->Off();
		RendererGroup.push_back(NewRenderer);
	}
}

void UI_Buff::Update(float _Delta)
{

}
