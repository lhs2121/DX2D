#include "PreCompile.h"
#include "Player.h"
#include "Portal.h"
#include "MapleLevel.h"
#include "StatData.h"
#include "MapleMap.h"
#include "DamageIndicator.h"
#include "Monster.h"

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
	ChangeState(PlayerState::IDLE);
}

void Player::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	MonsterCheck(_Delta);
	ItemCheck();
	CameraFocus();
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

void Player::ChangeRandomSwingAnimation()
{
	int RandomNumber = GameEngineRandom::GameEngineRandom().RandomInt(1, 3);
	std::string AnimationName = "swing" + std::to_string(RandomNumber);
	Renderer->ChangeAnimation(AnimationName);
}

void Player::PushDamage(std::vector<float> _DamageGroup)
{
	for (size_t i = 0; i < _DamageGroup.size(); i++)
	{
		Stat->CurHp -= _DamageGroup[i];
	}
	float4 Pos = Transform.GetWorldPosition() + float4(0.0f, 68.0f);
	DamageRenderer->RenderDamage(Pos, DamageColor::Purple, _DamageGroup, GameEngineRandom::GameEngineRandom().RandomInt(0, 999999));

}
void Player::MonsterCheck(float _Delta)
{
	HitDelay -= _Delta;
	if (HitDelay <= 0.0f)
	{
		Col->Collision(CollisionOrder::MonsterAttack, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
			{
				std::shared_ptr<Monster> monster = _Collision[0]->GetActor()->GetDynamic_Cast_This<Monster>();
				float Damage = monster->GetStat()->GetDamage();
				std::vector<float> DamageGroup = { Damage };
				PushDamage(DamageGroup);
				HitDelay = HitDelayReset;
			});
	}
}

std::shared_ptr<Monster> Player::GetCloseTarget()
{
	std::shared_ptr<Monster> Target = nullptr;
	DetectedCol->Collision(CollisionOrder::MonsterAttack, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
		{
			Target = _Collision[0]->GetActor()->GetDynamic_Cast_This<Monster>();
		});
	return Target;
}