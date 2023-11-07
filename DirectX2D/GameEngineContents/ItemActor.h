#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "UI_Inventory.h"

class ItemActor : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemActor();
	~ItemActor();

	// delete Function
	ItemActor(const ItemActor& _Other) = delete;
	ItemActor(ItemActor&& _Other) noexcept = delete;
	ItemActor& operator=(const ItemActor& _Other) = delete;
	ItemActor& operator=(ItemActor&& _Other) noexcept = delete;

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

