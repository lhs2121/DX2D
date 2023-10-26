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

	void StartSkill(float4 _Pos, float _DamageValue, DamageColor _Color);

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

