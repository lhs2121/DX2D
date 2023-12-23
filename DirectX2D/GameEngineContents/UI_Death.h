#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class UI_Death : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Death();
	~UI_Death();

	// delete Function
	UI_Death(const UI_Death& _Other) = delete;
	UI_Death(UI_Death&& _Other) noexcept = delete;
	UI_Death& operator=(const UI_Death& _Other) = delete;
	UI_Death& operator=(UI_Death&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> Notice;
	std::shared_ptr<class GameEngineUIRenderer> OKButton;
	std::shared_ptr<class GameEngineCollision> Col;
};

