#include "PreCompile.h"
#include "UI_Inventory.h"
#include "UI_Slot.h"

UI_Inventory* UI_Inventory::Inst = nullptr;

UI_Inventory::UI_Inventory()
{
}

UI_Inventory::~UI_Inventory()
{
}

void UI_Inventory::Start()
{
	{
		Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetRenderOrder(UIRenderOrder::PlayerUI);
		Renderer->SetSprite("InvenPanel");
	}
	
	{
		Draggable::Start();
		DragCol->Transform.SetLocalScale({ Renderer->GetImageTransform().GetLocalScale().X, 20.0f });
		DragCol->Transform.SetLocalPosition({ 0.0f,Renderer->GetImageTransform().GetLocalScale().hY() - 10.0f});
	}

	for (int i = 0; i < SlotSizeX * SlotSizeY; i++)
	{
		int x = i % SlotSizeX;  // x값을 0, 1, 2, 3으로 주기적으로 반복
		int y = i / SlotSizeX;  // y값을 0에서 시작하여 6까지 증가한 뒤 다시 0으로 초기화

		std::shared_ptr<UI_Slot> NewSlot = GetLevel()->CreateActor<UI_Slot>();
		NewSlot->Transform.SetWorldPosition(Transform.GetWorldPosition());
		NewSlot->Transform.AddLocalPosition(float4(35.0f * x, 0.0f));
		NewSlot->Transform.AddLocalPosition(float4(-60.0f, 100.0f - 35.0f * y));
		NewSlot->SetParent(this, i);
		SlotGroup.push_back(NewSlot);
	}

	GameEngineInput::AddInputObject(this);
}

void UI_Inventory::Update(float _Delta)
{
	Draggable::Update(_Delta);
}

void UI_Inventory::LevelEnd(GameEngineLevel* _NextLevel)
{

	Death();
}

void UI_Inventory::On()
{
	GameEngineActor::On();
	for (int i = 0; i < SlotGroup.size(); i++)
	{
		SlotGroup[i]->On();
	}

}

void UI_Inventory::Off()
{
	GameEngineActor::Off();
	for (int i = 0; i < SlotGroup.size(); i++)
	{
		SlotGroup[i]->Off();
	}
}

void UI_Inventory::AddItem(ItemInfo Info)
{
	for (int i = 0; i < SlotGroup.size(); i++)
	{
		if (SlotGroup[i]->IsEmpty() == true)
		{
			SlotGroup[i]->AddItem(Info);
			return;
		}
		else
		{
			if (SlotGroup[i]->IsSameItem(Info) == true)
			{
				if (SlotGroup[i]->IsFull() == false)
				{
					SlotGroup[i]->AddItem(Info);
					return;
				}
			}
		}
	}
}

void UI_Inventory::SwapItem(std::shared_ptr<class UI_Slot> Caller, std::shared_ptr<class UI_Slot> Callee)
{
	ItemInfo Temp;
	Temp = Caller->GetItemInfo();
	Caller->ReplaceItem(Callee->GetItemInfo());
	Callee->ReplaceItem(Temp);
}

void UI_Inventory::OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
	OffSet = Transform.GetWorldPosition() - _MouseCol->Transform.GetWorldPosition();
}

void UI_Inventory::OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
	Transform.SetWorldPosition(_MouseCol->Transform.GetWorldPosition());
	Transform.AddWorldPosition(OffSet);
}
