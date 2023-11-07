#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_Inventory.h"
#include "Draggable.h"

// Ό³Έν :
class UI_Item : public Draggable
{
public:
	// constrcuter destructer
	UI_Item();
	~UI_Item();

	// delete Function
	UI_Item(const UI_Item& _Other) = delete;
	UI_Item(UI_Item&& _Other) noexcept = delete;
	UI_Item& operator=(const UI_Item& _Other) = delete;
	UI_Item& operator=(UI_Item&& _Other) noexcept = delete;

	void UseItem();
	void SetItemImage(std::string SpriteName);
	void ClearItemImage();
protected:
	void Start() override;
	void Update(float _Delta) override;

	void OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;
	void OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;
	void OnEndDrag() override;

	std::shared_ptr<class GameEngineUIRenderer> ItemRenderer;
};