#include "PreCompile.h"
#include "UI_Item.h"

UI_Item::UI_Item()
{
}

UI_Item::~UI_Item()
{
}

void UI_Item::SetCollisionScale(float4 _Scale)
{
	SetDragColScale(_Scale);
}

void UI_Item::Start()
{
	Draggable::Start();
	ItemRenderer = CreateComponent<GameEngineUIRenderer>();
	ItemRenderer->AutoSpriteSizeOn();
	ItemRenderer->SetRenderOrder(UIRenderOrder::PlayerUI3);
	ItemRenderer->SetSprite("null");
}

void UI_Item::Update(float _Delta)
{
	Draggable::Update(_Delta);
}

void UI_Item::UseItem()
{
}

void UI_Item::AddItem(ItemInfo _Info)
{
	ItemRenderer->SetSprite(_Info.ItemSpriteName);
	if (IsUpdate() == false)
	{
		On();
	}
}

void UI_Item::ClearItem()
{
	ItemRenderer->SetSprite("null");
	Off();
}
