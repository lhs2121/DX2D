#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Inventory : public GameEngineActor
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

	static Inventory* Inst;
private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> Renderer;
};

