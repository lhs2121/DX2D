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
	void ChangeMpGauge(float _Value);

	float HpGaugeSizeX;
	float MpGaugeSizeX;
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
};

