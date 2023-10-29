#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Skill : public GameEngineActor
{
public:
	// constrcuter destructer
	Skill();
	~Skill();

	// delete Function
	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;

	virtual void StartSkill() {};
protected:
	void FlipX(int _dir, std::shared_ptr<class GameEngineSpriteRenderer> _Renderer);
	void Start() override;
	void Update(float _Delta) override;

};

