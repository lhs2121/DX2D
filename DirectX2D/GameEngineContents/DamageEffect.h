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

	void SetNumber(DamageColor _Color,int RendererNumber, int _Value);
	void MoveRendererPos(int RendererNumber, float4 _Pos);
	void SetRenderOrder(int RendererNumber, int _Order);

	float GetCoolTime()
	{
		return cool;
	}
	void StartSkill();
	void EndEffect();

	int CurOrder;
protected:
	void Start() override;
	void Update(float _Delta) override;

	float cool = 1.5f;
	int RendererSize = 2;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RendererGroup;
};

