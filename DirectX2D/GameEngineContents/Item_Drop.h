#pragma once
#include "PhysicsActor.h"
#include "UI_Inventory.h"

class Item_Drop : public PhysicsActor
{
public:
	// constrcuter destructer
	Item_Drop();
	~Item_Drop();

	// delete Function
	Item_Drop(const Item_Drop& _Other) = delete;
	Item_Drop(Item_Drop&& _Other) noexcept = delete;
	Item_Drop& operator=(const Item_Drop& _Other) = delete;
	Item_Drop& operator=(Item_Drop&& _Other) noexcept = delete;

	void Setting(float4 _Pos, std::string _SpriteName, int _DropRate);
	void AddItem();
protected:
	void Start() override;
	void Update(float _Delta) override;
	float SwingDir = 1;
	float SwingValue = 0;
	ItemInfo Info;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};

