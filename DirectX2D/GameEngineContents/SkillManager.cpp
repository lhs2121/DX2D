#include "PreCompile.h"
#include "SkillManager.h"
#include "Skill.h"
#include "Skill_FlashJump.h"
#include "Skill_LuckySeven.h"
#include "Skill_ShowDown.h"

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
		LuckySeven->On();
		break;
	case SkillType::ShowDown:
		ShowDown->On();
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
	
	FlashJump = GetLevel()->CreateActor<Skill_FlashJump>();
	LuckySeven = GetLevel()->CreateActor<Skill_LuckySeven>();
	ShowDown = GetLevel()->CreateActor<Skill_ShowDown>();
}

void SkillManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	FlashJump->Death();
	FlashJump = nullptr;
	LuckySeven->Death();
	LuckySeven = nullptr;
	ShowDown->Death();
	ShowDown = nullptr;

}
