#include "PreCompile.h"
#include "UI_Inventory.h"

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
	Renderer->SetSprite("Inventory");
	Renderer->Off();
	GameEngineInput::AddInputObject(this);
}

void UI_Inventory::Update(float _Delta)
{
	if (InputIsDown('I'))
	{
		if (Renderer->IsUpdate())
		{
			Renderer->Off();
		}
		else
		{
			Renderer->On();
		}
		
	}
}
