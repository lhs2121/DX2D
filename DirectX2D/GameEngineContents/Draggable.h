#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Draggable : public GameEngineActor
{
public:
	// constrcuter destructer
	Draggable();
	~Draggable();

	// delete Function
	Draggable(const Draggable& _Other) = delete;
	Draggable(Draggable&& _Other) noexcept = delete;
	Draggable& operator=(const Draggable& _Other) = delete;
	Draggable& operator=(Draggable&& _Other) noexcept = delete;

	void SetDragColScale(float4 _Scale);
protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineCollision> DragCol;
};

