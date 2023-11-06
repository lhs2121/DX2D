#include "PreCompile.h"
#include "Draggable.h"

Draggable* Draggable::CurDragUI = nullptr;

Draggable::Draggable()
{
}

Draggable::~Draggable()
{
}

void Draggable::SetDragColScale(float4 _Scale)
{
	DragCol->Transform.SetLocalScale(_Scale);
}

void Draggable::Start()
{
	DragCol = CreateComponent<GameEngineCollision>(CollisionOrder::UI_Drag);
	DragCol->SetCollisionType(ColType::AABBBOX2D);
	DragCol->Transform.SetLocalScale({ 100,100 });

	GameEngineInput::AddInputObject(this);
}

void Draggable::Update(float _Delta)
{
	if (InputIsDown(VK_LBUTTON))
	{
		DragCol->Collision(CollisionOrder::Cursor, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Col)
			{
				CurDragUI = this;
				MouseCol = _Col[0];
				OnStartDrag(MouseCol);
			});
	}

	if (CurDragUI != this)
	{
		return;
	}

	if (InputIsPress(VK_LBUTTON))
	{
		OnDrag(MouseCol);
	}

	if (InputIsUp(VK_LBUTTON))
	{
		OnEndDrag();
		CurDragUI = nullptr;
		MouseCol = nullptr;
	}

}

void Draggable::OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
}

void Draggable::OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol)
{
}

void Draggable::OnEndDrag()
{
}
