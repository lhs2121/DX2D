#pragma once

enum class RenderOrder
{
	KerningCityBG,
	Play,
	Effect,
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
	Player,
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