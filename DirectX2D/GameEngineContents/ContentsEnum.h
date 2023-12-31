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
	Cursor
};

enum class ActorOrder
{
	Map,
	Player,
	Monster,
	Portal,
	DamageEffect,
	Manager,
	Stat,
	Item,
	FadeScreen,
	UI,
	UI_Inventory,
	UI_Item,
};

enum class CollisionOrder
{
	Player,
	Monster,
	MonsterAttack,
	Boss,
	BossAttack,
	PlayerAttack,
	Portal,
	Item,
	UI_Drag,
	UI_Grab,
	UI_Button,
	UI_Slot,
	UI_Item,
	Cursor
};

enum class SkillType
{
	Body,
	FlashJump,
	LuckySeven,
	QuadrupleThrow,
	ShowDown,
	SurekenBooster,
	Haste
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

