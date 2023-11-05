#pragma once
#include "Draggable.h"
// Ό³Έν :
struct ItemInfo
{
	std::string ItemName;
	std::string ItemSpriteName;
	int ItemCount = 1;
	int MaxCount = 1;
};

class UI_Inventory : public Draggable
{
public:
	// constrcuter destructer
	UI_Inventory();
	~UI_Inventory();

	// delete Function
	UI_Inventory(const UI_Inventory& _Other) = delete;
	UI_Inventory(UI_Inventory&& _Other) noexcept = delete;
	UI_Inventory& operator=(const UI_Inventory& _Other) = delete;
	UI_Inventory& operator=(UI_Inventory&& _Other) noexcept = delete;

	void AddItem(ItemInfo Info);
	static UI_Inventory* Inst;
private:
	void Start() override;
	void Update(float _Delta) override;

	void RemoveItem(int SlotNum);

	int SlotSizeX = 4;
	int SlotSizeY = 6;
	std::shared_ptr<class GameEngineUIRenderer> Renderer;
	std::shared_ptr<class UI_Slot> Slots[6][4];
};

