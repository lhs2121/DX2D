#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BossState
{
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

	void BodyStart();
	void BodyUpdate(float _Delta);
	void BodyEnd();
	//Body

	void FireStart();
	void FireUpdate(float _Delta);
	void FireEnd();
	//Fire

	void PoisonStart();
	void PoisonUpdate(float _Delta);
	void PoisonEnd();
	//Poison

	void DiveStart();
	void DiveUpdate(float _Delta);
	void DiveEnd();
	//Dive

	void UltStart();
	void UltUpdate(float _Delta);
	void UltEnd();
	//Ult

	float Speed = 150.0f;
	BossState CurState;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::vector<std::shared_ptr<class GameEngineCollision>> PoisonDownCol;
	std::vector<std::shared_ptr<class GameEngineCollision>> PoisonAreaCol;
};

