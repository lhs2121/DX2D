#include "PreCompile.h"
#include "UI_Item.h"

UI_Item::UI_Item()
{
}

UI_Item::~UI_Item()
{
}

void UI_Item::Setting(float4 _Scale)
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

void UI_Item::OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{ 
}

void UI_Item::OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
	Transform.SetWorldPosition(_MouseCol->Transform.GetWorldPosition());
}


void UI_Item::OnEndDrag()
{
	Transform.SetLocalPosition({0.0f,0.0f});
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
