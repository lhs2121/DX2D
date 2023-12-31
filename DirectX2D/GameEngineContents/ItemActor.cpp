#include "PreCompile.h"
#include "ItemActor.h"
#include "UI_Inventory.h"

ItemActor::ItemActor()
{
}

ItemActor::~ItemActor()
{
}

void ItemActor::Setting(float4 _Pos, std::string _SpriteName, int _DropRate)
{
	Transform.SetWorldPosition(_Pos);

	int Random = GameEngineRandom::GameEngineRandom().RandomInt(0, 100);

	if (Random < _DropRate)
	{
		Info.ItemSpriteName = _SpriteName;
		Info.ItemName = _SpriteName; 
		Renderer->SetSprite(_SpriteName);
	}
	else
	{
		Info.ItemSpriteName = "Meso_Bronze";
		Info.ItemName = "Meso_Bronze";
		Renderer->ChangeAnimation("Meso_Bronze");
	}
}

void ItemActor::AddItem()
{
	UI_Inventory::Inst->AddItem(Info);
	Death();
}

void ItemActor::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->AutoSpriteSizeOn();
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->CreateAnimation("Meso_Bronze", "Meso_Bronze", 0.1f);
	Renderer->CreateAnimation("Meso_Gold", "Meso_Gold", 0.1f);
	Renderer->CreateAnimation("Meso_Bundle", "Meso_Bundle", 0.1f);

	Col = CreateComponent<GameEngineCollision>(CollisionOrder::Item);
	Col->SetCollisionType(ColType::SPHERE2D);
	Col->Transform.SetLocalScale({ 20,20 });
}

void ItemActor::Update(float _Delta)
{
	if (abs(Renderer->Transform.GetLocalPosition().Y) > 5.0f)
	{
		Renderer->Transform.SetLocalPosition({ 0.0f,SwingDir * 5.0f });
		SwingDir *= -1;
	}

	Renderer->Transform.AddLocalPosition({ 0.0f,SwingDir * 5.0f * _Delta });
}
