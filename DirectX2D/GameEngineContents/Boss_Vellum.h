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
	void FireUpdate();
	void FireEnd();
	//Fire

	void PoisonStart();
	void PoisonUpdate();
	void PoisonEnd();
	//Poison

	void DiveStart();
	void DiveUpdate();
	void DiveEnd();
	//Dive

	void UltStart();
	void UltUpdate();
	void UltEnd();
	//Ult

	void ColCheck();

	
	BossState CurState;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class DamageEffectController> DamageViewer;
};

