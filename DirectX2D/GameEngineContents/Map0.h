#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Map0 : public GameEngineActor
{
public:
	static Map0* MainMap;
	// constrcuter destructer
	Map0();
	~Map0();

	// delete Function
	Map0(const Map0& _Other) = delete;
	Map0(Map0&& _Other) noexcept = delete;
	Map0& operator=(const Map0& _Other) = delete;
	Map0& operator=(Map0&& _Other) noexcept = delete;

	float4 GetMapScale();
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer1;
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer2;

	float4 mapScale;
};

 