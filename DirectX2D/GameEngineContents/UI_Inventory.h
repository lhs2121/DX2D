#pragma once
#include "Draggable.h"
// Ό³Έν :
struct ItemInfo
{
	std::string ItemName = "";
	std::string ItemSpriteName = "";
	int ItemCount = 1;
	int MaxCount = 2;
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

	static UI_Inventory* Inst;

	void AddItem(ItemInfo Info);
	void SwapItem(std::shared_ptr<class UI_Slot> _Left, std::shared_ptr<class UI_Slot> _Right);
	void On() override;
	void Off() override;
private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void OnStartDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;
	void OnDrag(std::shared_ptr<class GameEngineCollision> _MouseCol) override;

	int SlotSizeX = 4;
	int SlotSizeY = 6;
	float4 OffSet;
	std::vector<std::shared_ptr<class UI_Slot>> SlotGroup;
	std::shared_ptr<class GameEngineUIRenderer> Renderer;
};

