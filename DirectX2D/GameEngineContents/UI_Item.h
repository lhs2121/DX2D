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

	void Setting(float4 _Scale);

	void UseItem();
	void AddItem(ItemInfo _Info);
	void ClearItem();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;
	void OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;
	void OnEndDrag() override;

	int ItemCount = 0;
	int MaxCount = 1;
	int SlotNum;
	float4 StartPos;
	float4 OffSet;
	std::shared_ptr<class GameEngineUIRenderer> CountRenderer0;
	std::shared_ptr<class GameEngineUIRenderer> CountRenderer1;
	std::shared_ptr<class GameEngineUIRenderer> CountRenderer2;
	std::shared_ptr<class GameEngineUIRenderer> ItemRenderer;
};