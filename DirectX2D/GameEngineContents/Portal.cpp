#include "PreCompile.h"
#include "Portal.h"
#include "ContentsEnum.h"
#include "Map0.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetSprite("portal");
	Renderer->CreateAnimation("portal", "portal", 0.1f, 0, 7);
	Renderer->ChangeAnimation("portal");
	Transform.SetLocalPosition({ 310, -910, 0.0f });
}

void Portal::Update(float _Delta)
{
}
