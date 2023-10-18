#pragma once
#include "MapleLevel.h"

// Ό³Έν :
class KerningCity : public MapleLevel
{
public:
	// constrcuter destructer
	KerningCity();
	~KerningCity();

	// delete Function
	KerningCity(const KerningCity& _Other) = delete;
	KerningCity(KerningCity&& _Other) noexcept = delete;
	KerningCity& operator=(const KerningCity& _Other) = delete;
	KerningCity& operator=(KerningCity&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class DamageEffectController> CurDamageEffectController;
};

