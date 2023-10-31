#include "PreCompile.h"
#include "Skill_ThorwSureken.h"
#include "Projectile.h"
#include "Player.h"

Skill_ThorwSureken::Skill_ThorwSureken()
{
}

Skill_ThorwSureken::~Skill_ThorwSureken()
{
}

void Skill_ThorwSureken::Start()
{
	Skill::Start();
}

void Skill_ThorwSureken::Update(float _Delta)
{

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
	float4 Pos = Player::MainPlayer->Transform.GetWorldPosition();
	float Dir = Player::MainPlayer->GetDir();
	int ID = GameEngineRandom::GameEngineRandom().RandomInt(0, 99999999);

	for (size_t i = 0; i < ThrowCount; i++)
	{
		float Delay = 0.4f + 0.1f * i;
		std::vector<float> Damage = Player::MainPlayer->GetStat()->GetDamage(1, SkillType::LuckySeven);
		CurProjectile = GetNonUpdateProjectile();
		CurProjectile->Setting(Pos, 500.0f, Dir, 2.0f, Delay);
		CurProjectile->SetDamage(Damage, ID);
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
