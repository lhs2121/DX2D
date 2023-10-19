#pragma once

enum class RenderOrder
{
	MapBackground,
	MapTile,
	MapObject,
	Monster,
	Projectile,
	Effect,
	Player,
	Effect2,
	Debug,
};

enum class ActorOrder
{
	Map,
	Player,
	Monster,
	NPC,
	MapObject,
	Skill,
	Projectile,
	SkillEffect,
	DamageEffect,
	Manager,
	PlayerStat,
	MonsterStat,
	UI
};

enum class CollisionOrder
{
	Player = 10,
	Monster,
	PlayerWeapon,
	MonsterWeapon,
	Portal
};

enum class StatDatae
{
	IDLE,
	WALK,
	JUMP,
	DOWN,
	ROPE,
	HIT,
	FLASHJUMP,
	LUCKYSEVEN,
	
};

enum class PlayerDirState
{
	LEFT,
	RIGHT,
};

enum class EffectType
{
	FlashJump,
	LuckySeven,
	HitSureken
};