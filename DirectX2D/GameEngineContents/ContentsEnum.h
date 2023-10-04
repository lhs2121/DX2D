#pragma once

enum class ContentsRenderType
{
	KCityMap,
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
