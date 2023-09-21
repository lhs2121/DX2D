#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Portal : public GameEngineActor
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;
protected:

	void Start() override;
	void Update(float _Delta) override;
};

