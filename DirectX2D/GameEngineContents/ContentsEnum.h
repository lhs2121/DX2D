#pragma once

enum class RenderOrder
{
	MapBackground,
	MapTile,
	MapObject,
	Monster,
	Sureken,
	Effect,
	Player,
	Effect2,
	Debug
};

enum class UIRenderOrder
{
	PlayerUI,
	PlayerUI2,
	PlayerUI3,
	FadeScreen,
	DebugUI,
};

enum class ActorOrder
{
	Map,
	Player,
	Monster,
	Boss,
	NPC,
	MapObject,
	Skill,
	Sureken,
	SkillEffect,
	DamageEffect,
	Manager,
	PlayerStat,
	MonsterStat,
	FadeScreen,
	UI
};

enum class CollisionOrder
{
	Player = 10,
	Monster,
	PlayerSkill,
	MonsterSkill,
	Portal
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
	HitSureken,
	ShowDown,
};

enum class FadeType
{
	FADEIN,
	FADEOUT
};

enum class DamageColor
{
	Orange,
	Red,
	Purple
};