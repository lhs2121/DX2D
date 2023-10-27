#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :

class DamageEffect;
class DamageIndicator : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageIndicator();
	~DamageIndicator();

	// delete Function
	DamageIndicator(const DamageIndicator& _Other) = delete;
	DamageIndicator(DamageIndicator&& _Other) noexcept = delete;
	DamageIndicator& operator=(const DamageIndicator& _Other) = delete;
	DamageIndicator& operator=(DamageIndicator&& _Other) noexcept = delete;

	void RenderDamage(float4 _Pos, float _DamageValue, int _HitCount, DamageColor _Color);

private:
	void Start() override;

	std::shared_ptr<DamageEffect> GetNonUpdateObject(std::list<std::shared_ptr<DamageEffect>> _list);
	std::vector<int> GetIntArray(float _Value);
	
};

