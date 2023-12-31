#pragma once
#include <GameEngineCore\GameEngineActor.h>
// ���� :
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
	static Draggable* CurDragUI;
protected:
	void Start() override;
	void Update(float _Delta) override;
	virtual void OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol);
	virtual void OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol);
	virtual void OnEndDrag();
	std::shared_ptr<class GameEngineCollision> DragCol;
	std::shared_ptr<class GameEngineCollision> MouseCol;
};

