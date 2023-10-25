#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class StatusBar : public GameEngineActor
{
	friend class StatManager;
public:
	// constrcuter destructer
	StatusBar();
	~StatusBar();

	// delete Function
	StatusBar(const StatusBar& _Other) = delete;
	StatusBar(StatusBar&& _Other) noexcept = delete;
	StatusBar& operator=(const StatusBar& _Other) = delete;
	StatusBar& operator=(StatusBar&& _Other) noexcept = delete;

	static StatusBar* Inst;

	void ChangeHpGauge(float _Value);
	void ResetHpGauge();

	void ChangeMpGauge(float _Value);
	void ResetMpGauge();

	void ChangeExpGauge(float _Value);
	void ResetExpGauge();

	void LevelUp(int Level);

	float4 HpGaugeSize;
	float4 MpGaugeSize;
private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineUIRenderer> StatusCover;

	std::shared_ptr<class GameEngineUIRenderer> LvText;
	std::shared_ptr<class GameEngineUIRenderer> LvNumber1;
	std::shared_ptr<class GameEngineUIRenderer> LvNumber2;
	std::shared_ptr<class GameEngineUIRenderer> LvNumber3;

	std::shared_ptr<class GameEngineUIRenderer> HpGauge;
	std::shared_ptr<class GameEngineUIRenderer> MpGauge;
	std::shared_ptr<class GameEngineUIRenderer> GaugeNumber;

	std::shared_ptr<class GameEngineUIRenderer> ExpGauge;
	std::shared_ptr<class GameEngineUIRenderer> ExpBG;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover2;
	std::shared_ptr<class GameEngineUIRenderer> ExpCover3;
	std::shared_ptr<class GameEngineUIRenderer> ExpNumber;
};

