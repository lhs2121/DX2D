#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :

class DamageEffect;
class DamageEffectController : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageEffectController();
	~DamageEffectController();

	// delete Function
	DamageEffectController(const DamageEffectController& _Other) = delete;
	DamageEffectController(DamageEffectController&& _Other) noexcept = delete;
	DamageEffectController& operator=(const DamageEffectController& _Other) = delete;
	DamageEffectController& operator=(DamageEffectController&& _Other) noexcept = delete;

	void StartEffect(float4 _Pos, float _DamageValue, DamageColor _Color);

private:
	std::shared_ptr<DamageEffect> GetUsableEffect(std::list<std::shared_ptr<DamageEffect>> _list);
	std::vector<int> GetIntArray(float _Value);
	float4 GetSpawnPos(float4 _Pos);
	void CountStack();
	void Start() override;
	
	
	float4 PrevSpawnPos;
	std::shared_ptr<DamageEffect> PrevEffect;
	int CurStack = 0;
	float StackCoolTime = 0.5f;
};

