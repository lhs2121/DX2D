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

	void Setting(float4 _Pos, DamageColor _Color, std::vector<int> _NumArray, int _Order, float _StartDelayTime, int _ID);
	int GetID() { return DamageID; }
private:
	void Start() override;
	void Update(float _Delta) override;
	void RendererOn();
	void RendererOff();

	int DamageID;
	float CoolTime = 0.5f;
	float StartDelayTime;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RendererGroup;
};

