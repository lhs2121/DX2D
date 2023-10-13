#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MapleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MapleLevel();
	~MapleLevel();

	// delete Function
	MapleLevel(const MapleLevel& _Other) = delete;
	MapleLevel(MapleLevel&& _Other) noexcept = delete;
	MapleLevel& operator=(const MapleLevel& _Other) = delete;
	MapleLevel& operator=(MapleLevel&& _Other) noexcept = delete;

	std::shared_ptr<class Portal> CreatePortal(std::string _NextLevel, float4 _Pos);

	std::shared_ptr<class Portal> GetPortal(std::string _NextLevel)
	{
		return PortalGroup[_NextLevel];
	};

	std::map<std::string, std::shared_ptr<class Portal>> PortalGroup;

	void Start() override;
};

