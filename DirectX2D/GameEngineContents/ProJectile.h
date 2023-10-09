#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ProJectile : public GameEngineActor
{
public:
	// constrcuter destructer
	ProJectile();
	~ProJectile();

	// delete Function
	ProJectile(const ProJectile& _Other) = delete;
	ProJectile(ProJectile&& _Other) noexcept = delete;
	ProJectile& operator=(const ProJectile& _Other) = delete;
	ProJectile& operator=(ProJectile&& _Other) noexcept = delete;

	void SetDir(float _Dir)
	{
		Dir = _Dir;
	}
	float GetDir()
	{
		return Dir;
	}
	void SetCoolTime(float _CoolTime)
	{
		CoolTime = _CoolTime;
	}
private:
	void Move(float _Delta);

	void ColCheck();
	void StartCoolTime(float _Delta);
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 400.0f;
	float CoolTime = 1.0f;
	float Dir;

	std::shared_ptr<class GameEngineCollision> Col;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
};

