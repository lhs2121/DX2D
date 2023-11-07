#include "PreCompile.h"
#include "UI_Slot.h"
#include "UI_Item.h"
#include "UI_Inventory.h"

UI_Slot::UI_Slot()
{
}

UI_Slot::~UI_Slot()
{
}

bool UI_Slot::IsEmpty()
{
	if (Info.ItemName == "")
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

	Col = CreateComponent<GameEngineCollision>(CollisionOrder::UI_Slot);
	Col->Transform.SetLocalScale({20,20});
	Col->SetCollisionType(ColType::AABBBOX2D);


	for (size_t i = 0; i < 4; i++)
	{
		std::shared_ptr<GameEngineUIRenderer> NewRenderer = CreateComponent<GameEngineUIRenderer>();
		NewRenderer->AutoSpriteSizeOn();
		NewRenderer->SetRenderOrder(UIRenderOrder::PlayerUI3);
		NewRenderer->Transform.SetLocalPosition({ -12.0f + 6.0f * i,-12.0f });
		NewRenderer->SetSprite("null");
		CountRenderers.push_back(NewRenderer);
	}

	ClearItem();

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
		SetCountImage(Info.ItemCount);
		return;
	}

	Info = _Info;
	SetCountImage(Info.ItemCount);
	ItemActor->SetItemImage(_Info.ItemSpriteName);

	if(!ItemActor->IsUpdate())
	ItemActor->On();
}

void UI_Slot::ReplaceItem(ItemInfo _Info)
{
	Info = _Info;

	if (_Info.ItemName == "")
	{
		ClearItem();
		return;
	}

	SetCountImage(Info.ItemCount);
	ItemActor->SetItemImage(Info.ItemSpriteName);

	if (!ItemActor->IsUpdate())
		ItemActor->On();
}

void UI_Slot::ClearItem()
{
	Info.ItemName = "";
	Info.ItemSpriteName = "";
	Info.ItemCount = 0;
	Info.MaxCount = 0;
	for (size_t i = 0; i < CountRenderers.size(); i++)
	{
		CountRenderers[i]->SetSprite("null");
	}

	ItemActor->ClearItemImage();
	ItemActor->Off();
}


void UI_Slot::SetCountImage(int CurItemCount)
{
	std::string CountStr = std::to_string(CurItemCount);
	for (size_t i = 0; i < CountStr.size(); i++)
	{
		int Num = CountStr[i] - '0';
		CountRenderers[i]->SetSprite("GaugeNumber", Num);
	}
}