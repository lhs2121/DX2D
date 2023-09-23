#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class KCityMap : public GameEngineActor
{
public:
	static KCityMap* MainMap;
	// constrcuter destructer
	KCityMap();
	~KCityMap();

	// delete Function
	KCityMap(const KCityMap& _Other) = delete;
	KCityMap(KCityMap&& _Other) noexcept = delete;
	KCityMap& operator=(const KCityMap& _Other) = delete;
	KCityMap& operator=(KCityMap&& _Other) noexcept = delete;

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

 