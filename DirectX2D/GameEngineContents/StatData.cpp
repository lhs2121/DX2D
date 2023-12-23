#include "PreCompile.h"
#include "StatData.h"

StatDataPlayer::StatDataPlayer(const StatDataPlayer& _Other)
{
	CurLevel = _Other.CurLevel;
	CurHp = _Other.CurHp;
	MaxHp = _Other.MaxHp;
	DEF = _Other.DEF;
	CurMp = _Other.CurMp;
	MaxMp = _Other.MaxMp;
	CurExp = _Other.CurExp;
	MaxExp = _Other.MaxExp;
	CurMoney = _Other.CurMoney;
	STR = _Other.STR;
	DEX = _Other.DEX;
	INT = _Other.INT;
	LUK = _Other.LUK;
	ATK = _Other.ATK;
	AtkRate = _Other.AtkRate;
	DmgRate = _Other.DmgRate;
	BossDmgRate = _Other.BossDmgRate;
	CriDmg = _Other.CriDmg;
	CriRate = _Other.CriRate;
}
