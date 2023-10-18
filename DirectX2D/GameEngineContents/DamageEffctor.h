#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class DamageEffect;
class DamageEffctor : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageEffctor();
	~DamageEffctor();

	// delete Function
	DamageEffctor(const DamageEffctor& _Other) = delete;
	DamageEffctor(DamageEffctor&& _Other) noexcept = delete;
	DamageEffctor& operator=(const DamageEffctor& _Other) = delete;
	DamageEffctor& operator=(DamageEffctor&& _Other) noexcept = delete;

	void StartEffect(float4 _Pos, float _DamageValue);

private:
	void Start() override;
	void Update(float _Delta) override;

	float4 PrevGruopPos;
	int Stack = 0;
	float StackCoolTime = 0.5f;
	std::shared_ptr<DamageEffect> GetUsableEffect(std::list<std::shared_ptr<DamageEffect>> _list);
	std::shared_ptr<DamageEffect> PrevEffect;
};

