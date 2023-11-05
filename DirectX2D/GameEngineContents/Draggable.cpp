#include "PreCompile.h"
#include "Draggable.h"

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
	if (InputIsPress(VK_LBUTTON))
	{
		DragCol->Collision(CollisionOrder::Cursor, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Col)
			{
				Transform.SetWorldPosition(_Col[0]->Transform.GetWorldPosition());
			});
	}
}
