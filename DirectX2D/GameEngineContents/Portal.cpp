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
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Portal);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 50,100 });
		Col->Transform.SetLocalPosition({ 0,60 });
	}

	Renderer = CreateComponent<GameEngineSpriteRenderer>(1);
	Renderer->SetRenderOrder(RenderOrder::MapObject);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->CreateAnimation("portal", "portal", 0.1f, 0, 7);
	Renderer->ChangeAnimation("portal");
	Renderer->AutoSpriteSizeOn();
	Renderer->Transform.SetLocalPosition({ 0,-5.0f });
}

void Portal::Update(float _Delta)
{
	
}
