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
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->SetRenderOrder(UIRenderOrder::PlayerUI);
	Renderer->SetSprite("InvenPanel");
	Renderer->Off();
	Draggable::Start();
	DragCol->Transform.SetLocalScale({ Renderer->GetImageTransform().GetLocalScale().X, 10.0f });
	DragCol->Transform.SetLocalPosition({ 0.0f,Renderer->GetImageTransform().GetLocalScale().hY()});

	for (int y = 0; y < SlotSizeY; y++)
	{
		for (int x = 0; x < SlotSizeX; x++)
		{
			static int num = 0;
			std::shared_ptr<UI_Slot> NewSlot = GetLevel()->CreateActor<UI_Slot>();
			NewSlot->Transform.SetWorldPosition(Transform.GetWorldPosition());
			NewSlot->Transform.AddLocalPosition(float4(35.0f * x, 0.0f));
			NewSlot->Transform.AddLocalPosition(float4(-60.0f, 100.0f - 35.0f * y));

			float4 a = NewSlot->Transform.GetWorldPosition();
			NewSlot->SetParent(this, num);
			NewSlot->Setting();
			num++;
			Slots[y][x] = NewSlot;
		}
	}

	GameEngineInput::AddInputObject(this);
}

void UI_Inventory::Update(float _Delta)
{
	Draggable::Update(_Delta);
	if (InputIsDown('I'))
	{
		if (Renderer->IsUpdate())
		{
			Renderer->Off();
			for (int y = 0; y < SlotSizeY; y++)
			{
				for (int x = 0; x < SlotSizeX; x++)
				{
					Slots[y][x]->Off();
				}
			}
		}
		else
		{
			Renderer->On();
			for (int y = 0; y < SlotSizeY; y++)
			{
				for (int x = 0; x < SlotSizeX; x++)
				{
					Slots[y][x]->On();
				}
			}
		}

	}
}

void UI_Inventory::AddItem(ItemInfo Info)
{
	for (int y = 0; y < SlotSizeY; y++)
	{
		for (int x = 0; x < SlotSizeX; x++)
		{
			if (Slots[y][x]->IsEmpty() == true)
			{
				Slots[y][x]->AddItem(Info);
				return;
			}
			else
			{
				if (Slots[y][x]->IsSameItem(Info) == true)
				{
					if (Slots[y][x]->IsFull() == false)
					{
						Slots[y][x]->AddItem(Info);
						return;
					}
				}
			}
		}
	}
}

void UI_Inventory::RemoveItem(int SlotNum)
{
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
