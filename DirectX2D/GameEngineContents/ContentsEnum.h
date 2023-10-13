#pragma once

enum class RenderOrder
{
	MapBackground,
	MapTile,
	MapObject,
	Player,
	Monster,
	Projectile,
	Effect,
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
	Effect
};

enum class CollisionOrder
{
	Player = 10,
	Monster,
	PlayerWeapon,
	MonsterWeapon,
	Portal
};

enum class PlayerState
{
	IDLE,
	WALK,
	JUMP,
	DOWN,
	ROPE,
	ATTACK,
	LUCKYSEVEN
};

enum class PlayerDirState
{
	LEFT,
	RIGHT,
};

enum class SkillType
{
	FlashJump,
	LuckySeven,

};