#include "PreCompile.h"
#include "Player.h"
#include "Portal.h"
#include "MapleLevel.h"
#include "StatData.h"
#include "MapleMap.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	PlayerBase::Start();
	GameEngineInput::AddInputObject(this);
	ChangeDirState(PlayerDirState::LEFT);
	ChangeState(PlayerState::IDLE);
}

void Player::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	PlayerBase::Update(_Delta);
	FlipRenderer();
	CameraFocus();
	DirUpdate();
	RopePivotUpdate();
	RopeCheck();
	PortalCheck();
	MoveUpdate();
	StateUpdate(_Delta);
}

void Player::Release()
{

}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayerBase::LevelStart(_PrevLevel);
	IsFadeIn = false;
	ChangeState(PlayerState::IDLE);

	if (_PrevLevel == nullptr)
	{
		float4 StartPos = MapleMap::CurMap->GetMapScale().Half();
		Transform.SetWorldPosition({ StartPos.X, -StartPos.Y });
		return;
	}

	std::string name = _PrevLevel->GetName();
	MapleLevel* Level = GetLevel()->GetDynamic_Cast_This<MapleLevel>().get();
	std::shared_ptr<Portal> portal = Level->GetPortal(name);
	if (portal != nullptr)
	{
		Transform.SetWorldPosition(portal->Transform.GetWorldPosition() + float4(0, -70));
		GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y,-600.0f });
	}
	else
	{
		float4 StartPos = MapleMap::CurMap->GetMapScale().Half();
		Transform.SetWorldPosition({ StartPos.X, -StartPos.Y });
	}

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	if (CameraPos.X - ContentsCore::GetStartWindowSize().hX() < 0.0f)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::RIGHT);
			float X = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X - ContentsCore::GetStartWindowSize().hX();
			if (X >= 0)
			{
				break;
			}
		}
	}
	if (CameraPos.X + ContentsCore::GetStartWindowSize().hX() > MapleMap::CurMap->GetMapScale().X)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::LEFT);
			float X = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X + ContentsCore::GetStartWindowSize().hX();
			if (X <= MapleMap::CurMap->GetMapScale().X)
			{
				break;
			}
		}
	}
	if (CameraPos.Y - ContentsCore::GetStartWindowSize().hY() < -MapleMap::CurMap->GetMapScale().Y)
	{
		while (true)
		{
			GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::UP);
			float Y = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y - ContentsCore::GetStartWindowSize().hY();
			if (Y >= -MapleMap::CurMap->GetMapScale().Y)
			{
				break;
			}
		}
	}
}

void Player::FlipRenderer()
{
	if (CanFlip == false)
	{
		return;
	}

	float4 Scale = Renderer->Transform.GetLocalScale();

	if (Scale.X == 1 && NetForce.X > 0)
	{
		Renderer->Transform.SetLocalScale({ -1.0f,1.0f,1.0f });
	}
	if (Scale.X == -1 && NetForce.X < 0)
	{
		Renderer->Transform.SetLocalScale({ 1.0f,1.0f,1.0f });
	}

}

void Player::ChangeRandomSwingAnimation()
{
	int RandomNumber = GameEngineRandom::GameEngineRandom().RandomInt(1, 3);
	std::string AnimationName = "swing" + std::to_string(RandomNumber);
	Renderer->ChangeAnimation(AnimationName);
}

