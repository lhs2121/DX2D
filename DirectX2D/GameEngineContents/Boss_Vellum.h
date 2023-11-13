#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BossState
{
	Move,
	Body,
	Fire,
	Dive,
	Poison,
	Ult
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

protected:
	void Start() override;
	void Update(float _Delta) override;

	void StateUpdate(float _Delta);
	void ChangeState(BossState _State);
	void SetNextState();
	void SetDir();

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

	BossState PrevState;
	BossState CurState;
	BossState NextState;

	float MoveDuration;

	int BodyProb = 20;
	int FireProb = 20;
	int	DiveProb = 40;
	int	PoisonProb = 20;
	int	UltProb = 0;

	int CurHp = 50000;
	int MaxHp = 50000;
	int PoisonAttackCount = 0;
	float Speed = 100.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::vector<std::shared_ptr<class GameEngineCollision>> PoisonDownCol;
	std::vector<std::shared_ptr<class GameEngineCollision>> PoisonAreaCol;
};

