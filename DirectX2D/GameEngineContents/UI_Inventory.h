#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class UI_Inventory : public GameEngineActor
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
private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> Renderer;
};

