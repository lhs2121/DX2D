#include "PreCompile.h"
#include "PoisonArea.h"

PoisonArea::PoisonArea()
{
}

PoisonArea::~PoisonArea()
{
}

void PoisonArea::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->SetRenderOrder(RenderOrder::Debug);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->CreateAnimation("Poison_Area", "Poison_Area");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetFrameEvent("Poison_Area", 21, [&](GameEngineSpriteRenderer*)
		{
			Col->On();
		});
	Renderer->SetFrameEvent("Poison_Area", 23, [&](GameEngineSpriteRenderer*)
		{
			Col->Off();
		});
	Renderer->SetEndEvent("Poison_Area", [&](GameEngineSpriteRenderer*)
		{
			Off();
		});
	Renderer->ChangeAnimation("Poison_Area");

	Col = CreateComponent<GameEngineCollision>(CollisionOrder::BossAttack);
	Col->SetCollisionType(ColType::AABBBOX2D);
	Col->Transform.SetLocalScale({ 100,100 });
	Col->Transform.AddLocalPosition({ 0,50 });
	Col->Off();

	Off();
}

void PoisonArea::Update(float _Delta)
{

}