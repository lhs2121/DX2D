#pragma once

enum class RenderType
{
	KerningCityBG,
	Play,
};

enum class ActorType
{
	Map,
	Player,
	Monster,
	NPC,
	MapObject,
	Skill
};

enum class CollisionType
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