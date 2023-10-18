#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class DamageEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageEffect();
	~DamageEffect();

	// delete Function
	DamageEffect(const DamageEffect& _Other) = delete;
	DamageEffect(DamageEffect&& _Other) noexcept = delete;
	DamageEffect& operator=(const DamageEffect& _Other) = delete;
	DamageEffect& operator=(DamageEffect&& _Other) noexcept = delete;

	void SetNumber(int _Value);
	void MovePos(float4 _Pos);
	void SetRenderOrder(int _Order)
	{
		Renderer->SetRenderOrder(_Order);
		CurOrder = _Order;
	}
	float GetCoolTime()
	{
		return cool;
	}
	void StartEffect();
	void EndEffect();
	int CurOrder;
protected:
	void Start() override;
	void Update(float _Delta) override;
	float cool = 1.5f;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

