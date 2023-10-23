#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <list>

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

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<class Player> CurPlayer;
	std::shared_ptr<class MapleMap> CurMap;
	std::shared_ptr<class BulletShooter> CurShooter;
	std::shared_ptr<class SkillEffctor> CurSkillEffctor;
	std::shared_ptr<class StatusBar> CurStatusBar;
	std::shared_ptr<class ExpBar> CurExpBar;
	std::shared_ptr<class FadeScreen> CurFadeScreen;

	std::map<std::string, std::shared_ptr<class Portal>> PortalGroup;
};

