#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class UI_Buff : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Buff();
	~UI_Buff();

	// delete Function
	UI_Buff(const UI_Buff& _Other) = delete;
	UI_Buff(UI_Buff&& _Other) noexcept = delete;
	UI_Buff& operator=(const UI_Buff& _Other) = delete;
	UI_Buff& operator=(UI_Buff&& _Other) noexcept = delete;

	static std::shared_ptr<UI_Buff> Inst;
	void RenderBuffUI(SkillType _Type);
private:
	void Start() override;
	void Update(float _Delta) override;

	std::vector<std::shared_ptr<class GameEngineUIRenderer>> RendererGroup;
};

