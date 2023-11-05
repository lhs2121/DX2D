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

protected:
	void FlipX(float _dir, std::shared_ptr<class GameEngineSpriteRenderer> _Renderer);
};

