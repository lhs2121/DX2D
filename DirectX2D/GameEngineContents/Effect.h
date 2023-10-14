#pragma once
#include <GameEngineCore\GameEngineActor.h>
// Ό³Έν :
class Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect();
	~Effect();

	// delete Function
	Effect(const Effect& _Other) = delete;
	Effect(Effect&& _Other) noexcept = delete;
	Effect& operator=(const Effect& _Other) = delete;
	Effect& operator=(Effect&& _Other) noexcept = delete;


	void ChangeAnimation(std::string _String);
	void FlipX(int _dir);
protected:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

