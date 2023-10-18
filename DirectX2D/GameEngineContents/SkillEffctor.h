#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class SkillEffect;
class SkillEffctor : public GameEngineActor
{
public:
	// constrcuter destructer
	SkillEffctor();
	~SkillEffctor();

	// delete Function
	SkillEffctor(const SkillEffctor& _Other) = delete;
	SkillEffctor(SkillEffctor&& _Other) noexcept = delete;
	SkillEffctor& operator=(const SkillEffctor& _Other) = delete;
	SkillEffctor& operator=(SkillEffctor&& _Other) noexcept = delete;

	void StartEffect(float4 _Pos, EffectType _Type, float dir);

	static SkillEffctor* Inst;
protected:
	std::shared_ptr<SkillEffect> GetUsableEffect(std::list<std::shared_ptr<SkillEffect>> _list);
	void Start() override;
	void Update(float _Delta) override;

};

