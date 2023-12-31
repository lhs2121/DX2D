#include "PreCompile.h"
#include "Skill_ThorwSureken.h"
#include "Projectile.h"
#include "Player.h"
#include "Monster.h"
#include "StatManager.h"

Skill_ThorwSureken::Skill_ThorwSureken()
{
}

Skill_ThorwSureken::~Skill_ThorwSureken()
{
}

void Skill_ThorwSureken::Start()
{
	Skill::Start();
	MonsterDetector = CreateComponent<GameEngineCollision>();
	MonsterDetector->SetCollisionType(ColType::AABBBOX2D);
	MonsterDetector->Transform.SetLocalScale({ 100,20 });
}

void Skill_ThorwSureken::Release()
{
	CurProjectile = nullptr;

	std::list<std::shared_ptr<Projectile>>::iterator Start = ProjectileGroup.begin();
	std::list<std::shared_ptr<Projectile>>::iterator End = ProjectileGroup.end();

	for (; Start != End; Start++)
	{
		(*Start)->Death();
		(*Start) = nullptr;
	}
}

void Skill_ThorwSureken::StartSkill()
{
	float4 Pos = Player::MainPlayer->Transform.GetWorldPosition() + float4(0.0f,33.0f);
	float PlayerDir = Player::MainPlayer->GetDir();
	int ID = GameEngineRandom::GameEngineRandom().RandomInt(0, 99999999);

	float4 MonsterSize = float4::ZERO;
	std::shared_ptr<Monster> Target = Player::MainPlayer->GetCloseTarget();
	if (Target != nullptr)
	{
		MonsterSize = Target->GetImageSize();
	}
	
	for (int i = 0; i < ThrowCount; i++)
	{
		// 일단 타겟에게 데미지를 적용한다
		std::vector<float> Damage = StatManager::Inst->GetDamage(1, SkillType::LuckySeven);
		if (Target != nullptr)
		{
			Target->ApplyDamage(Damage); // 몬스터의 attackcol이 꺼진다
		}

		float4 Dir = float4(PlayerDir, 0);
		Dir.VectorRotationToDegZ(3 - 1.5f*i);

		float Delay = 0.2f + 0.1f * i;
		CurProjectile = GetNonUpdateProjectile();
		CurProjectile->Setting(Pos, 700.0f, Dir, 0.5f, Delay);
		CurProjectile->SetDamage(Damage, ID);
		CurProjectile->SetTarget(Target);
		CurProjectile->SetHitPosOffset(MonsterSize - ((MonsterSize/ThrowCount) * i));
	}
}

std::shared_ptr<class Projectile> Skill_ThorwSureken::GetNonUpdateProjectile()
{
	std::list<std::shared_ptr<Projectile>>::iterator Start = ProjectileGroup.begin();
	std::list<std::shared_ptr<Projectile>>::iterator End = ProjectileGroup.end();

	for (; Start != End; Start++)
	{
		if ((*Start)->IsUpdate() == false)
		{
			return (*Start);
		}
	}

	std::shared_ptr<Projectile> NewProjectile = GetLevel()->CreateActor<Projectile>(199);
	ProjectileGroup.push_back(NewProjectile);
	return NewProjectile;
}
