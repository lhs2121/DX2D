#include "PreCompile.h"
#include "Inventory.h"

Inventory* Inventory::Inst = nullptr;

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->SetSprite("Inventory");
	Renderer->Off();
	GameEngineInput::AddInputObject(this);
}

void Inventory::Update(float _Delta)
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
