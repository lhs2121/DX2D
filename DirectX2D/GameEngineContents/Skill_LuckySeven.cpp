#include "PreCompile.h"
#include "Skill_LuckySeven.h"
#include "Projectile.h"
#include "Player.h"

Skill_LuckySeven::Skill_LuckySeven()
{
}

Skill_LuckySeven::~Skill_LuckySeven()
{
}

void Skill_LuckySeven::Start()
{
	{
		//Renderer->CreateAnimation("LuckySeven", "LuckySeven", 0.1f, 0, 6, false);
		//Renderer->ChangeAnimation("LuckySeven");
	}
}

void Skill_LuckySeven::Update(float _Delta)
{

}

void Skill_LuckySeven::Release()
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

void Skill_LuckySeven::StartSkill()
{
	float4 Pos = Player::MainPlayer->Transform.GetWorldPosition();
	float Dir = Player::MainPlayer->GetDir();

	CurProjectile = GetNonUpdateProjectile();
	CurProjectile->Setting(Pos, 500.0f, Dir, 2.0f, 0.4f);

	CurProjectile = GetNonUpdateProjectile();
	CurProjectile->Setting(Pos, 500.0f, Dir, 2.0f, 0.5f);

	CurProjectile = GetNonUpdateProjectile();
	CurProjectile->Setting(Pos, 500.0f, Dir, 2.0f, 0.6f);

	CurProjectile = GetNonUpdateProjectile();
	CurProjectile->Setting(Pos, 500.0f, Dir, 2.0f, 0.7f);
}

std::shared_ptr<class Projectile> Skill_LuckySeven::GetNonUpdateProjectile()
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
