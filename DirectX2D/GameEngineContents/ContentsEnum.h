#pragma once

enum class ContentsRenderType
{
	KerningCityBG,
	Play,
};


enum class ContentsObjectType
{
	Map,
	Player,
	Monster,
	NPC,
	MapObject,
	Skill
};

enum class ContentsCollisionType
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
