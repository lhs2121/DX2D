#include "PreCompile.h"
#include "Portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::SetNextMap(std::string _NextLevel)
{
	Col->SetName(_NextLevel);
}

std::string Portal::GetNextMap()
{
	return Col->GetName();
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
}

void Portal::Update(float _Delta)
{

}
