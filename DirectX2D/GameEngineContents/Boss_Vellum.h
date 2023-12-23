#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BossState
{
	Move,
	Body,
	Fire,
	Dive,
	Poison,
	Ult,
	Die
};

// Ό³Έν :
class Boss_Vellum : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Vellum();
	~Boss_Vellum();

	// delete Function
	Boss_Vellum(const Boss_Vellum& _Other) = delete;
	Boss_Vellum(Boss_Vellum&& _Other) noexcept = delete;
	Boss_Vellum& operator=(const Boss_Vellum& _Other) = delete;
	Boss_Vellum& operator=(Boss_Vellum&& _Other) noexcept = delete;

	void RenderDamage(std::vector<float> _DamageGroup, int _DamageID, int _Order = 0);
	void ApplyDamage(std::vector<float> _DamageGroup);
protected:
	void Start() override;
	void Update(float _Delta) override;

	void StateUpdate(float _Delta);
	void ChangeState(BossState _State);
	void SetNextState();
	void SetRendererDir();

	void MoveStart();
	void MoveUpdate(float _Delta);
	void MoveEnd();

	void BodyStart();
	void BodyUpdate(float _Delta);
	void BodyEnd();

	void FireStart();
	void FireUpdate(float _Delta);
	void FireEnd();

	void PoisonStart();
	void PoisonUpdate(float _Delta);
	void PoisonEnd();

	void DiveStart();
	void DiveUpdate(float _Delta);
	void DiveEnd();

	void UltStart();
	void UltUpdate(float _Delta);
	void UltEnd();

	void DieStart();
	void DieUpdate(float _Delta);
	void DieEnd();

	void PoisonSetting();

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	BossState PrevState;
	BossState CurState;
	BossState NextState;

	float MoveDuration;

	int BodyProb = 40;
	int FireProb = 40;
	int	DiveProb = 0;
	int	PoisonProb = 20;
	int	UltProb = 0;

	int CurHp = 20000000;
	int MaxHp = 20000000;
	int PoisonAttackCount = 0;
	int UltAttackCount = 0;
	float Speed = 100.0f;

	float Dir;

	float PoisonInterTime = 5.0f;

	float4 BodyColScale = { 300, 400 };
	float4 FireColScale = { 300,400 };

	float4 LeftClosePos = { -500,200 };
	float4 LeftMidPos = { -800,200 };
	float4 LeftLongPos = { -1000,200 };

	float4 RightClosePos = { 500,200 };
	float4 RightMidPos = { 800,200 };
	float4 RightLongPos = { 1000,200 };

	float4 LeftUltPos;
	float4 RightUltPos;

	std::shared_ptr<class UI_Boss_HpBar> HpBar;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class GameEngineCollision> BodyCol;
	std::shared_ptr<class GameEngineCollision> FireCol;
	std::shared_ptr<class DamageIndicator> DamageRenderer;
	std::vector<std::shared_ptr<class PoisonArea>> PoisonAreas;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> UltScreenRenderer;
};

