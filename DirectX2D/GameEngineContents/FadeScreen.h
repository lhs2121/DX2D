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

	void SettingAndStart(FadeType _Type, std::string _NextLevelStr = "");

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	FadeType CurType;
	std::string NextLevelStr;
	float AlphaValue = 0.0f;
	std::shared_ptr<class GameEngineUIRenderer> Renderer;

};

