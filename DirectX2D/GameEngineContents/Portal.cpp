#include "PreCompile.h"
#include "Portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::SetNextMap(std::string _MapName)
{
	Col->SetName(_MapName);
}

void Portal::Start()
{
	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Portal);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 50,100 });
		Col->Transform.SetLocalPosition({ 0,-70 });
	}

	Renderer = CreateComponent<GameEngineSpriteRenderer>(1);
	Renderer->SetRenderOrder(-5);
	Renderer->SetSprite("portal");
	Renderer->CreateAnimation("portal", "portal", 0.1f, 0, 7);
	Renderer->ChangeAnimation("portal");
	Transform.SetLocalPosition({ 310, -910, 0.0f });
}

void Portal::Update(float _Delta)
{
}
