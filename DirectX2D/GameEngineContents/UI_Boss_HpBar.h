#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UI_Boss_HpBar : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Boss_HpBar();
	~UI_Boss_HpBar();

	// delete Function
	UI_Boss_HpBar(const UI_Boss_HpBar& _Other) = delete;
	UI_Boss_HpBar(UI_Boss_HpBar&& _Other) noexcept = delete;
	UI_Boss_HpBar& operator=(const UI_Boss_HpBar& _Other) = delete;
	UI_Boss_HpBar& operator=(UI_Boss_HpBar&& _Other) noexcept = delete;

	void AddHpGauge(float _Value);
protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> HpCover;
	std::shared_ptr<class GameEngineUIRenderer> HpGauge;
	std::shared_ptr<class GameEngineUIRenderer> HpBG;
	std::shared_ptr<class GameEngineUIRenderer> Mark;
};