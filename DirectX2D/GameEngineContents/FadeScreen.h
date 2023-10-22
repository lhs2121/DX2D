#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FadeScreen : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeScreen();
	~FadeScreen();

	// delete Function
	FadeScreen(const FadeScreen& _Other) = delete;
	FadeScreen(FadeScreen&& _Other) noexcept = delete;
	FadeScreen& operator=(const FadeScreen& _Other) = delete;
	FadeScreen& operator=(FadeScreen&& _Other) noexcept = delete;

	void StartFadeIn(std::string _NextLevelString);
	void StartFadeOut();
protected:
	void Start() override;
	void Update(float _Delta) override;

};

