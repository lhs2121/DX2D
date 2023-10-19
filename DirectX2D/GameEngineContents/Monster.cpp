#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	MonsterBase::Start();
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>();
		Renderer->CreateAnimation("m0stand", "m0stand", 0.2f);
		Renderer->ChangeAnimation("m0stand");
		Renderer->SetPivotType(PivotType::Bottom);
		Renderer->SetRenderOrder(RenderOrder::Monster);
		Renderer->AutoSpriteSizeOn();
		Renderer->SetAutoScaleRatio(1);
		ImageSize = Renderer->GetCurSprite().Texture->GetScale();
		Col->Transform.SetLocalScale(ImageSize);
		Col->Transform.SetLocalPosition({ 0,ImageSize.hY() });
		int a = 0;
	}
}
void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	MonsterBase::Update(_Delta);
}
