#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Effect;
class EffectManager : public GameEngineActor
{
public:
	// constrcuter destructer
	EffectManager();
	~EffectManager();

	// delete Function
	EffectManager(const EffectManager& _Other) = delete;
	EffectManager(EffectManager&& _Other) noexcept = delete;
	EffectManager& operator=(const EffectManager& _Other) = delete;
	EffectManager& operator=(EffectManager&& _Other) noexcept = delete;

	void StartEffect(float4 _Pos, EffectType _Type, float dir);

	static EffectManager* Inst;
protected:
	std::shared_ptr<Effect> GetUsableEffect(std::list<std::shared_ptr<Effect>> _list);
	bool IsAleadyOnEffect(std::list<std::shared_ptr<Effect>> _list);
	void Start() override;
	void Update(float _Delta) override;

};

