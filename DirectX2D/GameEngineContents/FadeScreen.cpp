#include "PreCompile.h"
#include "FadeScreen.h"

FadeScreen::FadeScreen()
{
}

FadeScreen::~FadeScreen()
{
}

void FadeScreen::SettingAndStart(FadeType _Type, std::string _NextLevelStr)
{
	NextLevelStr = _NextLevelStr;
	CurType = _Type;

	switch (CurType)
	{
	case FadeType::FADEIN:
		Renderer->GetColorData().MulColor.A = 0.0f;
		AlphaValue = 0.0f;
		break;
	case FadeType::FADEOUT:
		Renderer->GetColorData().MulColor.A = 1.1f;
		AlphaValue = 1.1f;
		break;
	default:
		break;
	}
	On();
}

void FadeScreen::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->SetSprite("FadeScreen");
	Renderer->SetRenderOrder(UIRenderOrder::FadeScreen);
	Off();
}

void FadeScreen::Update(float _Delta)
{
	if (CurType == FadeType::FADEIN)
	{
		if (AlphaValue < 1)
		{
			AlphaValue += _Delta;
		}

		Renderer->GetColorData().MulColor.A = AlphaValue;

		if (AlphaValue >= 1.0f)
		{
			Off();
			GameEngineCore::ChangeLevel(NextLevelStr);
		}
	}
	else if (CurType == FadeType::FADEOUT)
	{
		if (AlphaValue > 0)
		{
			AlphaValue -= _Delta;
		}

		Renderer->GetColorData().MulColor.A = AlphaValue;

		if (AlphaValue <= 0.0f)
		{
			Off();
		}
	}
	
}

void FadeScreen::Release()
{

}
