#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class UI_BuffIcon : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_BuffIcon();
	~UI_BuffIcon();

	// delete Function
	UI_BuffIcon(const UI_BuffIcon& _Other) = delete;
	UI_BuffIcon(UI_BuffIcon&& _Other) noexcept = delete;
	UI_BuffIcon& operator=(const UI_BuffIcon& _Other) = delete;
	UI_BuffIcon& operator=(UI_BuffIcon&& _Other) noexcept = delete;

	void Setting(SkillType _Type);
private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> Renderer;
	float CoolTime;
};

