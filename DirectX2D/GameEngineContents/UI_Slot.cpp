#include "PreCompile.h"
#include "UI_Slot.h"
#include "UI_Item.h"
#include "UI_Inventory.h"

UI_Slot::UI_Slot()
{
	Info.ItemName = "";
	Info.ItemSpriteName = "";
	Info.ItemCount = 0;
	Info.MaxCount = 1;
}

UI_Slot::~UI_Slot()
{
}

bool UI_Slot::IsEmpty()
{
	if (Info.ItemCount == 0)
	{
		return true;
	}
	return false;
}

bool UI_Slot::IsSameItem(ItemInfo _Info)
{
	if (Info.ItemName == _Info.ItemName)
	{
		return true;
	}
	return false;
}

void UI_Slot::Setting()
{
	ItemActor->Setting(SlotRenderer->GetImageTransform().GetLocalScale());
}

bool UI_Slot::IsFull()
{
	if (Info.ItemCount >= Info.MaxCount)
	{
		return true;
	}
	return false;
}

void UI_Slot::Start()
{
	SlotRenderer = CreateComponent<GameEngineUIRenderer>();
	SlotRenderer->AutoSpriteSizeOn();
	SlotRenderer->SetRenderOrder(UIRenderOrder::PlayerUI2);
	SlotRenderer->SetSprite("Slot");
	
	ItemActor = GetLevel()->CreateActor<UI_Item>(ActorOrder::UI_Item);
	ItemActor->Transform.SetWorldPosition(Transform.GetWorldPosition());
	ItemActor->SetParent(this, 0);
	Off();
}

void UI_Slot::Update(float _Delta)
{
}

void UI_Slot::UseItem()
{
	Info.ItemCount += -1;
	if (Info.ItemCount == 0)
	{
		ClearItem();
	}
}

void UI_Slot::AddItem(ItemInfo _Info)
{
	if (Info.ItemName == _Info.ItemName)
	{
		Info.ItemCount++;
		return;
	}
	Info = _Info;
	ItemActor->AddItem(_Info);
}

void UI_Slot::ClearItem()
{
	Info.ItemName = "";
	Info.ItemSpriteName = "";
	Info.ItemCount = 0;
	Info.MaxCount = 1;
	ItemActor->ClearItem();
}
