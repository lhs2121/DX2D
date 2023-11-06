#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MouseActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseActor();
	~MouseActor();

	// delete Function
	MouseActor(const MouseActor& _Other) = delete;
	MouseActor(MouseActor&& _Other) noexcept = delete;
	MouseActor& operator=(const MouseActor& _Other) = delete;
	MouseActor& operator=(MouseActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

	float4 WinSize = ContentsCore::GetStartWindowSize().Half();
	std::shared_ptr<class GameEngineUIRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
};

