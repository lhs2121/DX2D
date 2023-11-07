#include "PreCompile.h"
#include "UI_Inventory.h"
#include "UI_Slot.h"
#include "UI_Item.h"

UI_Item::UI_Item()
{
}

UI_Item::~UI_Item()
{
}

void UI_Item::Start()
{
	DragCol = CreateComponent<GameEngineCollision>(CollisionOrder::UI_Drag);
	DragCol->SetCollisionType(ColType::AABBBOX2D);
	DragCol->Transform.SetLocalScale({ 15,15 });
	GameEngineInput::AddInputObject(this);

	{
		ItemRenderer = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer->AutoSpriteSizeOn();
		ItemRenderer->SetRenderOrder(UIRenderOrder::PlayerUI3);
		ItemRenderer->SetSprite("null");
	}

	Off();
}

void UI_Item::UseItem()
{
}

void UI_Item::SetItemImage(std::string SpriteName)
{
	ItemRenderer->SetSprite(SpriteName);
}

void UI_Item::ClearItemImage()
{
	ItemRenderer->SetSprite("null");
}


// µå·¡±× 
void UI_Item::Update(float _Delta)
{
	Draggable::Update(_Delta);
}

void UI_Item::OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
}

void UI_Item::OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
	Transform.SetWorldPosition(_MouseCol->Transform.GetWorldPosition());
}


void UI_Item::OnEndDrag()
{
	DragCol->Collision(CollisionOrder::UI_Slot, [&](std::vector<std::shared_ptr<GameEngineCollision>> _SlotCol)
		{
			UI_Inventory::Inst->SwapItem(GetParentObject()->GetDynamic_Cast_This<UI_Slot>(), _SlotCol[0]->GetActor()->GetDynamic_Cast_This<UI_Slot>());
		});
	Transform.SetLocalPosition({ 0.0f,0.0f });

}