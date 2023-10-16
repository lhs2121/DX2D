#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class ExpBar : public GameEngineActor
{
public:
	// constrcuter destructer
	ExpBar();
	~ExpBar();

	// delete Function
	ExpBar(const ExpBar& _Other) = delete;
	ExpBar(ExpBar&& _Other) noexcept = delete;
	ExpBar& operator=(const ExpBar& _Other) = delete;
	ExpBar& operator=(ExpBar&& _Other) noexcept = delete;

	void AddExpGauge(float _Value);

	static ExpBar* Inst;

private:
	void Start() override;
	void Update(float _Delta) override;
	

	std::shared_ptr<class GameEngineUIRenderer> ExpGauge;
	std::shared_ptr<class GameEngineUIRenderer> ExpBG;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover2;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover3;
	std::shared_ptr<class GameEngineUIRenderer> ExpNumber;
};

