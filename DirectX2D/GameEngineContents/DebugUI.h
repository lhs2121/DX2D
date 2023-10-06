#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class DebugUI : public GameEngineActor
{
public:
	// constrcuter destructer
	DebugUI();
	~DebugUI();

	// delete Function
	DebugUI(const DebugUI& _Other) = delete;
	DebugUI(DebugUI&& _Other) noexcept = delete;
	DebugUI& operator=(const DebugUI& _Other) = delete;
	DebugUI& operator=(DebugUI&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<class GameEngineUIRenderer> UIRenderer;
};

