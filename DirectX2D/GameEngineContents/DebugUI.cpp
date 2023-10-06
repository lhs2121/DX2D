#include "PreCompile.h"
#include "DebugUI.h"
#include <GameEngineCore\GameEngineUIRenderer.h>

DebugUI::DebugUI()
{
}

DebugUI::~DebugUI()
{
}

void DebugUI::Start()
{
	{
		UIRenderer = CreateComponent<GameEngineUIRenderer>(100);
		//UIRenderer->
	}
}

void DebugUI::Update(float _Delta)
{
}
