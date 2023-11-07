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

	void RenderDamage(float4 _Pos, DamageColor _Color, std::vector<float> _DamageGroup, int _DamageID = 1);
	void PlusRenderOrder(int _Order) { LastRenderOrder += _Order; };
private:
	void Start() override;

	int LastRenderOrder = 0;
	float4 PrevPos;
	std::shared_ptr<DamageEffect> PrevEffect = nullptr;
	std::shared_ptr<DamageEffect> GetNonUpdateObject(std::list<std::shared_ptr<GameEngineObject>> _list);
	std::vector<int> GetIntArray(float _Value);
	
};

