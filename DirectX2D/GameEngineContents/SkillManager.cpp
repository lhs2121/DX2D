#include "PreCompile.h"
#include "SkillManager.h"
#include "Skill.h"
#include "Skill_FlashJump.h"
#include "Skill_ThorwSureken.h"
#include "Skill_ShowDown.h"
#include "Skill_Booster.h"
#include "Skill_Haste.h"

SkillManager* SkillManager::Inst = nullptr;

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}


void SkillManager::StartSkill(SkillType _Type)
{
	switch (_Type)
	{
	case SkillType::FlashJump:
		FlashJump->StartSkill();
		break;
	case SkillType::LuckySeven:
		ThrowSureken->SetThrowCount(2);
		ThrowSureken->StartSkill();
		break;
	case SkillType::QuadrupleThrow:
		ThrowSureken->SetThrowCount(4);
		ThrowSureken->StartSkill();
		break;
	case SkillType::ShowDown:
		ShowDown->StartSkill();
		break;
	case SkillType::SurekenBooster:
		Booster->StartSkill();
		break;
	case SkillType::Haste:
		Haste->StartSkill();
		break;
	default:
		break;
	}

}

void SkillManager::Start()
{

}

void SkillManager::Update(float _Delta)
{

}

void SkillManager::LevelStart(GameEngineLevel* _PrevLevel)
{
	FlashJump = GetLevel()->CreateActor<Skill_FlashJump>(300);
	ThrowSureken = GetLevel()->CreateActor<Skill_ThorwSureken>(300);
	ShowDown = GetLevel()->CreateActor<Skill_ShowDown>(300);
	Haste = GetLevel()->CreateActor<Skill_Haste>(300);
	Booster = GetLevel()->CreateActor<Skill_Booster>(300);
}

void SkillManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	FlashJump->Death();
	FlashJump = nullptr;
	ThrowSureken->Death();
	ThrowSureken = nullptr;
	ShowDown->Death();
	ShowDown = nullptr;
	Haste->Death();
	Haste = nullptr;
	Booster->Death();
	Booster = nullptr;
}
