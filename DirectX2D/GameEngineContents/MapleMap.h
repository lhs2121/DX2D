#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MapleMap : public GameEngineActor
{
public:
	static std::shared_ptr<MapleMap> CurMap;
	// constrcuter destructer
	MapleMap();
	~MapleMap();

	// delete Function
	MapleMap(const MapleMap& _Other) = delete;
	MapleMap(MapleMap&& _Other) noexcept = delete;
	MapleMap& operator=(const MapleMap& _Other) = delete;
	MapleMap& operator=(MapleMap&& _Other) noexcept = delete;

	static void SetCurMap(std::shared_ptr<MapleMap> _Map);
	float4 GetMapScale();
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 0, 0, 0, 0 });
	void SwitchDebugRender();
protected:
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer;
	float4 MapScale;
	float4 StartingLocation;

};

