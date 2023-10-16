#pragma once
#include <GameEngineCore\GameEngineActor.h>

// Ό³Έν :
class MapleMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MapleMap();
	~MapleMap();

	// delete Function
	MapleMap(const MapleMap& _Other) = delete;
	MapleMap(MapleMap&& _Other) noexcept = delete;
	MapleMap& operator=(const MapleMap& _Other) = delete;
	MapleMap& operator=(MapleMap&& _Other) noexcept = delete;

	static MapleMap* CurMap;

	void SwitchDebugRender();

	float4 GetMapScale();

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 0, 0, 0, 0 });

protected:
	float4 MapScale;

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer;
};

