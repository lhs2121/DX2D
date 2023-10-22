#include "PreCompile.h"
#include "FadeScreen.h"

FadeScreen::FadeScreen()
{
}

FadeScreen::~FadeScreen()
{
}

void FadeScreen::StartFadeIn(std::string _NextLevelString)
{
	GameEngineCore::ChangeLevel(_NextLevelString);
}

void FadeScreen::StartFadeOut()
{
}

void FadeScreen::Start()
{
}

void FadeScreen::Update(float _Delta)
{
}
