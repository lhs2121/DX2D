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

	void SetNumber(DamageColor _Color, int RendererNumber, int _Value);

	void HorizontalAlign();

	void VerticalAlign();

	void RenderOrderAlign(int _Order);

	void RenderStart();

	void RenderEnd();

	int GetLastRenderOrder() { return LastOrder; }

	float GetCoolTime() { return cool; }


private:
	void Start() override;
	void Update(float _Delta) override;

	float cool = 1.5f;
	int LastOrder;
	int RendererSize = 2;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RendererGroup;
};

