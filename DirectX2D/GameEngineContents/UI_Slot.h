#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_Inventory.h"

// Ό³Έν :
class UI_Slot : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Slot();
	~UI_Slot();

	// delete Function
	UI_Slot(const UI_Slot& _Other) = delete;
	UI_Slot(UI_Slot&& _Other) noexcept = delete;
	UI_Slot& operator=(const UI_Slot& _Other) = delete;
	UI_Slot& operator=(UI_Slot&& _Other) noexcept = delete;

	bool IsEmpty();
	bool IsFull();
	bool IsSameItem(ItemInfo _Info);
    
	void SetSlotNumber(int _Num) { SlotNum = _Num; }
	int GetSlotNumber() { return SlotNum; }
	void AddItem(ItemInfo _Info);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void UseItem();
	void ClearItem();

	ItemInfo Info;
	int SlotNum;

	std::shared_ptr<class UI_Item> ItemActor;
	std::shared_ptr<class GameEngineUIRenderer> SlotRenderer;
	std::shared_ptr<class GameEngineCollision> Col;
};